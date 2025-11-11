const form = document.getElementById('convert-form');
const browseButton = document.getElementById('browse-source');
const sourceInput = document.getElementById('source-path');
const formatSelect = document.getElementById('format');
const resultContainer = document.getElementById('result');
const statusContainer = document.getElementById('env-status');

async function refreshEnvironmentStatus() {
  if (!window.electronAPI) {
    return;
  }
  const status = await window.electronAPI.getEnvironmentStatus();
  if (status.platform !== 'win32') {
    statusContainer.innerHTML =
      '<p class="warning">Windows is required to control Hancom HWP. Conversion will not run on this platform.</p>';
  } else if (!status.hasActiveXSupport) {
    statusContainer.innerHTML =
      '<p class="warning">Hancom HWP ActiveX control (winax) is unavailable. Install Hancom Office and ensure winax is installed.</p>';
  } else {
    statusContainer.textContent = 'Ready for conversion.';
  }
}

browseButton.addEventListener('click', async () => {
  const selected = await window.electronAPI.selectOdt();
  if (selected) {
    sourceInput.value = selected;
  }
});

form.addEventListener('submit', async (event) => {
  event.preventDefault();

  resultContainer.textContent = '';

  if (!sourceInput.value) {
    resultContainer.innerHTML = '<p class="error">Please select an ODT file.</p>';
    return;
  }

  const format = formatSelect.value;

  const defaultOutput = `${sourceInput.value.replace(/\.odt$/i, '')}.${format}`;
  const destination = await window.electronAPI.selectDestination(defaultOutput);

  if (!destination) {
    return;
  }

  const button = document.getElementById('convert-button');
  button.disabled = true;
  button.textContent = 'Converting…';

  const response = await window.electronAPI.convertDocument({
    sourcePath: sourceInput.value,
    outputDir: window.electronAPI.dirname(destination),
    format
  });

  button.disabled = false;
  button.textContent = 'Convert';

  if (!response.success) {
    resultContainer.innerHTML = `<p class="error">${response.message}</p>`;
    return;
  }

  resultContainer.innerHTML = `<p class="success">Saved to ${response.outputPath}</p>`;
});

refreshEnvironmentStatus();
