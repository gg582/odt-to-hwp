const form = document.getElementById('convert-form');
const browseButton = document.getElementById('browse-source');
const sourceInput = document.getElementById('source-path');
const formatSelect = document.getElementById('format');
const resultContainer = document.getElementById('result');
const statusContainer = document.getElementById('env-status');

// Create a hidden file input
const fileInput = document.createElement('input');
fileInput.type = 'file';
fileInput.accept = '.odt';
fileInput.style.display = 'none';
document.body.appendChild(fileInput);

statusContainer.innerHTML =
  '<p>This is the web version. File conversion is only available in the desktop application.</p>';

browseButton.addEventListener('click', () => {
  fileInput.click();
});

fileInput.addEventListener('change', () => {
  if (fileInput.files.length > 0) {
    sourceInput.value = fileInput.files[0].name;
  }
});

form.addEventListener('submit', async (event) => {
  event.preventDefault();
  resultContainer.innerHTML = '<p class="error">Conversion is not available in the web version. Please use the desktop app.</p>';
});
