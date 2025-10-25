const API_URL = "http://192.168.0.1"; // <-- zmień na swój adres ESP lub serwera

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

// ===== LED CONTROL =====
async function fetchLedState(id) {
  try {
    const res = await fetch(`${API_URL}/api/leds/${id}`);
    if (res.ok) {
      const data = await res.json();
      return data.state;
    }
  } catch (err) {
    console.error(err);
  }
  return null;
}

async function toggleLed(id) {
  try {
    const res = await fetch(`${API_URL}/api/leds/${id}/toggle`, { method: 'POST' });
    if (res.ok) {
      const data = await res.json();
      return data.state;
    }
  } catch (err) {
    console.error(err);
  }
  return null;
}

async function updateLedDisplay(id, ledEl) {
  const state = await fetchLedState(id);
  if (state === 'on') ledEl.classList.add('on');
  else ledEl.classList.remove('on');
}

// Button event listeners
led1Btn.addEventListener('click', async () => {
  await toggleLed(1);
  updateLedDisplay(1, led1El);
});

led2Btn.addEventListener('click', async () => {
  await toggleLed(2);
  updateLedDisplay(2, led2El);
});

// Initial fetch
updateLedDisplay(1, led1El);
updateLedDisplay(2, led2El);

// Auto-refresh every second
setInterval(() => {
  updateLedDisplay(1, led1El);
  updateLedDisplay(2, led2El);
}, 1000);

// ===== OTA UPDATE =====
let seconds = null, otaTimerVar = null;

fileInput.addEventListener("change", () => {
  if (fileInput.files.length > 0) {
    const file = fileInput.files[0];
    fileInfo.innerHTML = `<h4>File: ${file.name}<br>Size: ${file.size} bytes</h4>`;
  }
});

btnUpdate.addEventListener("click", () => {
  if (fileInput.files.length === 0) { alert('Wybierz plik najpierw'); return; }

  const file = fileInput.files[0];
  const formData = new FormData();
  formData.set("file", file, file.name);

  otaStatus.textContent = `Uploading ${file.name}, Firmware Update in Progress...`;

  const xhr = new XMLHttpRequest();
  xhr.upload.addEventListener("progress", updateProgress);
  xhr.open('POST', `${API_URL}/OTAupdate`);
  xhr.responseType = "blob";
  xhr.send(formData);
});

function updateProgress(event) { if(event.lengthComputable) getUpdateStatus(); }

function getUpdateStatus() {
  const xhr = new XMLHttpRequest();
  xhr.open('POST', `${API_URL}/OTAstatus`, false);
  xhr.send('ota_update_status');

  if(xhr.readyState === 4 && xhr.status === 200){
    const response = JSON.parse(xhr.responseText);
    latestFirmware.textContent = `${response.compile_date} - ${response.compile_time}`;

    if(response.ota_update_status === 1){ seconds=10; otaRebootTimer(); }
    else if(response.ota_update_status === -1){ otaStatus.textContent="!!! Upload Error !!!"; }
  }
}

function otaRebootTimer() {
  otaStatus.textContent = `OTA Firmware Update Complete. This page will close shortly, Rebooting in: ${seconds}`;
  if(--seconds===0){ clearTimeout(otaTimerVar); window.location.reload(); }
  else { otaTimerVar=setTimeout(otaRebootTimer,1000); }
}
