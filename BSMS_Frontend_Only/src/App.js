
import { useState } from "react";
import "./App.css";

function App() {
  const [connected, setConnected] = useState(false);
  const [spotStatus, setSpotStatus] = useState("N/A");
  const [spotsLeft, setSpotsLeft] = useState("N/A");
  const [bs1Status, setBs1Status] = useState("Waiting...");

  // Static statuses for now
  const spotStatuses = {
    1: spotStatus,
    2: "EMPTY SPOT",
    3: "BOOKED",
    4: "EMPTY SPOT",
    5: "EMPTY SPOT",
    6: "EMPTY SPOT",
    7: "EMPTY SPOT",
    8: "EMPTY SPOT",
    9: "EMPTY SPOT",
    10: "EMPTY SPOT",
  };

  const connectSerial = async () => {
    try {
      const port = await navigator.serial.requestPort();
      await port.open({ baudRate: 9600 });

      const decoder = new TextDecoderStream();
      port.readable.pipeTo(decoder.writable);
      const reader = decoder.readable.getReader();

      setConnected(true);

      let buffer = "";
      while (true) {
        const { value, done } = await reader.read();
        if (done) break;
        if (value) {
          buffer += value;
          const lines = buffer.split("\n");
          buffer = lines.pop();

          for (let line of lines) {
            line = line.trim();
            if (line.startsWith("SPOTS LEFT:")) {
              setSpotsLeft(line.replace("SPOTS LEFT:", "").trim());
            } else if (line.startsWith("SPOT 1 STATUS:")) {
              setSpotStatus(line.replace("SPOT 1 STATUS:", "").trim());
            } else if (line.startsWith("PARKING LOT SAFETY UPDATE:")) {
              setBs1Status(line.replace("PARKING LOT SAFETY UPDATE:", "").trim());
            }
          }
        }
      }
    } catch (err) {
      console.error("Serial connection error:", err);
    }
  };

  return (
    <div className="dashboard">
      <h1>BSMS Serial Dashboard</h1>
      {!connected ? (
        <button onClick={connectSerial}>Connect to BSMS</button>
      ) : (
        <div className="layout">
          <div className="live-data">
            <div className="card"><h2>Spot 1 Status</h2><p>{spotStatuses[1]}</p></div>
            <div className="card"><h2>Spot 2 Status</h2><p>{spotStatuses[2]}</p></div>
            <div className="card"><h2>Spot 3 Status</h2><p>{spotStatuses[3]}</p></div>
            <div className="card"><h2>Spot 4 Status</h2><p>{spotStatuses[4]}</p></div>
            <div className="card"><h2>Spot 5 Status</h2><p>{spotStatuses[5]}</p></div>
            <div className="card"><h2>Spot 6 Status</h2><p>{spotStatuses[6]}</p></div>
            <div className="card"><h2>Spot 7 Status</h2><p>{spotStatuses[7]}</p></div>
            <div className="card"><h2>Spot 8 Status</h2><p>{spotStatuses[8]}</p></div>
            <div className="card"><h2>Spot 9 Status</h2><p>{spotStatuses[9]}</p></div>
            <div className="card"><h2>Spot 10 Status</h2><p>{spotStatuses[10]}</p></div>
            <div className="card"><h2>Spots Left</h2><p>{spotsLeft}</p></div>
            <div className={`card ${bs1Status === "POTENTIAL ACCIDENT"  ? "alert" : ""}`}>
              <h2>Safety Update</h2>
              <p>BS 1: {bs1Status}</p>
              <p>BS 2: ALL CLEAR</p>
              <p>BS 3: ALL CLEAR</p>
              <p>BS 4: ALL CLEAR</p>
              <p>BS 5: ALL CLEAR</p>
            </div>
          </div>

          <div className="map-container">
            <h2>Blind Spot Map</h2>
            <div className="l-map">
              <div className="lane-line-horizontal"></div>
              <div className="lane-line-vertical"></div>

              {/* PS1 (Leave untouched) */}
              <div className="row">
                <div className={`spot ${spotStatus === "PERFECT POSITION" || spotStatus ==="TOO CLOSE"  ? "active" : "clear"}`}>PS1</div>
                <div className="spot clear">PS2</div>
                <div className="spot booked" title="Plate: EV 92089">PS3</div>
                <div className="spot clear">PS4</div>
              </div>
              {/* /* Check in the required time update when the page refreshes every 5 secs*/}
              <div className="vertical">
                <div className="spot clear">PS5</div>
                <div className="spot clear">PS6</div>
                <div className="spot clear">PS7</div>
                <div className="spot clear">PS8</div>
                <div className="spot clear">PS9</div>
                <div className="spot clear">PS10</div>
              </div>

              <div className={`bs-dot ${bs1Status === "POTENTIAL ACCIDENT" ? "active" : "clear"}`} />
              <div className="bs-label">BS 001</div>
            </div>
          </div>
        </div>
      )}
    </div>
  );
}

export default App;
