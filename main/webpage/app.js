let API_URL = "http://192.168.0.1"; // AP adress

// LED elements
const led1El = document.getElementById("led1");
const led2El = document.getElementById("led2");
const led1Btn = document.getElementById("led1-btn");
const led2Btn = document.getElementById("led2-btn");

// OTA elements
const fileInput = document.getElementById("selected_file");
const btnUpdate = document.getElementById("btnUpdate");
const fileInfo = document.getElementById("file_info");
const otaStatus = document.getElementById("ota_update_status");
const latestFirmware = document.getElementById("latest_firmware");

// Network elements
const btnGetNetwork = document.getElementById("btnGetNetwork");
const btnSaveNetwork = document.getElementById("btnSaveNetwork");
const ssidInput = document.getElementById("ssid");
const passwordInput = document.getElementById("password");
const networkStatus = document.getElementById("network_status");


// ===== TABS =====
document.querySelectorAll(".tab-btn").forEach(btn => {
  btn.addEventListener("click", () => {
    document.querySelectorAll(".tab").forEach(tab => tab.classList.remove("active"));
    document.querySelectorAll(".tab-btn").forEach(b => b.classList.remove("active"));
    document.getElementById(btn.dataset.tab).classList.add("active");
    btn.classList.add("active");
  });
});

// ===== LED CONTROL =====
async function fetchLedState(id) {
  try {
    const res = await fetch(`${API_URL}/api/leds/${id}`);
    if(res.ok) return (await res.json()).state;
  } catch(e) { console.error(e); }
  return null;
}

async function toggleLed(id) {
  try {
    const res = await fetch(`${API_URL}/api/leds/${id}/toggle`, { method: 'POST' });
    if(res.ok) return (await res.json()).state;
  } catch(e) { console.error(e); }
  return null;
}

async function updateLedDisplay(id, ledEl) {
  const state = await fetchLedState(id);
  if(state === 'on') ledEl.classList.add('on');
  else ledEl.classList.remove('on');
}

// Button events
led1Btn.addEventListener('click', async () => { await toggleLed(1); updateLedDisplay(1, led1El); });
led2Btn.addEventListener('click', async () => { await toggleLed(2); updateLedDisplay(2, led2El); });

// Initial fetch
updateLedDisplay(1, led1El);
updateLedDisplay(2, led2El);

// ===== OTA UPDATE =====
let seconds=null, otaTimerVar=null;

fileInput.addEventListener("change", () => {
  if(fileInput.files.length>0){
    const file = fileInput.files[0];
    fileInfo.innerHTML = `<h4>File: ${file.name}<br>Size: ${file.size} bytes</h4>`;
  }
});

btnUpdate.addEventListener("click", ()=>{
  if(fileInput.files.length===0){ alert("Wybierz plik najpierw"); return; }
  const file = fileInput.files[0];
  const formData = new FormData();
  formData.set("file", file, file.name);

  otaStatus.textContent = `Uploading ${file.name}, Firmware Update in Progress...`;
  const xhr = new XMLHttpRequest();
  xhr.upload.addEventListener("progress", updateProgress);
  xhr.open("POST", `${API_URL}/OTAupdate`);
  xhr.responseType="blob";
  xhr.send(formData);
});

function updateProgress(event){ if(event.lengthComputable) getUpdateStatus(); }

function getUpdateStatus(){
  const xhr = new XMLHttpRequest();
  xhr.open("POST", `${API_URL}/OTAstatus`, false);
  xhr.send("ota_update_status");
  if(xhr.readyState===4 && xhr.status===200){
    const resp=JSON.parse(xhr.responseText);
    latestFirmware.textContent=`${resp.compile_date} - ${resp.compile_time}`;
    if(resp.ota_update_status===1){ seconds=10; otaRebootTimer(); }
    else if(resp.ota_update_status===-1){ otaStatus.textContent="!!! Upload Error !!!"; }
  }
}

function otaRebootTimer(){
  otaStatus.textContent=`OTA Firmware Update Complete. Rebooting in: ${seconds}`;
  if(--seconds===0){ clearTimeout(otaTimerVar); window.location.reload(); }
  else{ otaTimerVar=setTimeout(otaRebootTimer,1000); }
}

// ===== NETWORK CONFIG =====
btnGetNetwork.addEventListener("click", async () => {
  try{
    const res = await fetch(`${API_URL}/api/config/network`);
    if(res.ok){
      const data = await res.json();
      ssidInput.value=data.ssid||"";
      passwordInput.value=data.password||"";
      networkStatus.textContent="Dane pobrane ✅";
    }
  } catch(e){ networkStatus.textContent="Błąd pobrania ❌"; console.error(e); }
});

btnSaveNetwork.addEventListener("click", async ()=>{
  const ssid = ssidInput.value;
  const password = passwordInput.value;
  try{
    const res = await fetch(`${API_URL}/api/config/network`, {
      method:"POST",
      headers:{ "Content-Type":"application/json" },
      body: JSON.stringify({ssid,password})
    });
    if(res.ok) networkStatus.textContent="Zapisano ✅";
    else networkStatus.textContent="Błąd zapisu ❌";
  } catch(e){ networkStatus.textContent="Błąd zapisu ❌"; console.error(e); }
});


// ===== FAST STA NETWORK DISCOVERY (PARALLEL BATCH SCANNING) =====
// Quickly scan 192.168.0.x for device's STA IP using parallel batches
async function discoverStaApiUrl() {
  const subnet = "192.168.0."; // adjust if needed
  const timeout = 400; // lower timeout = faster scan
  const batchSize = 50; // how many IP to scan at once
  let found = false;

  console.log("Starting FAST STA discovery...");

  // helper request function with timeout
  async function probeIp(testIp) {
    try {
      const controller = new AbortController();
      const timer = setTimeout(() => controller.abort(), timeout);

      const res = await fetch(`http://${testIp}/api/config/ip_addr`, {
        signal: controller.signal
      });

      clearTimeout(timer);

      if (res.ok) {
        const data = await res.json();
        if (data.ip && data.ip !== "0.0.0.0") {
          return testIp;
        }
      }
    } catch (e) {
      // no response
    }
    return null;
  }

  // process 254 addresses in batches
  for (let start = 1; start <= 254; start += batchSize) {
    const batch = [];

    for (let i = start; i < start + batchSize && i <= 254; i++) {
      batch.push(probeIp(`${subnet}${i}`));
    }

    const results = await Promise.all(batch);
    const hit = results.find(ip => ip !== null);

    if (hit) {
		console.log("FOUND STA device at:", hit);
		API_URL = `http://${hit}`; 
		found = true;
		break;
    }
  }

  if (!found) {
    console.log("STA device not found in subnet.");
  }
}

// run at startup
discoverStaApiUrl();

