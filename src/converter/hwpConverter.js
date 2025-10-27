const fs = require('fs');
const path = require('path');

let ActiveXObject;
try {
  ({ ActiveXObject } = require('winax'));
} catch (error) {
  ActiveXObject = null;
}

const SUPPORTED_FORMATS = {
  hwp: {
    extension: '.hwp',
    saveType: 'HWP'
  },
  hwpx: {
    extension: '.hwpx',
    saveType: 'HWPX'
  }
};

function assertWindowsPlatform() {
  if (process.platform !== 'win32') {
    throw new Error('Hancom HWP automation is only available on Windows.');
  }
}

function ensureOutputPath(sourcePath, outputDir, formatKey) {
  const { extension } = SUPPORTED_FORMATS[formatKey];
  const baseName = path.basename(sourcePath, path.extname(sourcePath));
  const directory = outputDir || path.dirname(sourcePath);
  return path.join(directory, `${baseName}${extension}`);
}

function convertOdtToHancom(sourcePath, options = {}) {
  if (!fs.existsSync(sourcePath)) {
    throw new Error('Source file does not exist.');
  }

  const formatKey = (options.format || 'hwp').toLowerCase();
  if (!SUPPORTED_FORMATS[formatKey]) {
    throw new Error(`Unsupported format: ${formatKey}`);
  }

  assertWindowsPlatform();

  if (!ActiveXObject) {
    throw new Error(
      'winax is not available. Ensure that the package is installed and the app is running on Windows.'
    );
  }

  const targetPath = ensureOutputPath(sourcePath, options.outputDir, formatKey);
  const { saveType } = SUPPORTED_FORMATS[formatKey];

  const hwp = new ActiveXObject('HWPFrame.HwpObject');
  try {
    const opened = hwp.Open(sourcePath);
    if (!opened) {
      throw new Error('Failed to open the ODT document.');
    }

    const result = hwp.SaveAs(targetPath, saveType, '');
    if (!result) {
      throw new Error('Conversion failed while invoking SaveAs.');
    }
  } finally {
    try {
      hwp.Quit();
    } catch (quitError) {
      // ignore quit errors to avoid masking conversion errors
    }
  }

  return targetPath;
}

function getEnvironmentStatus() {
  return {
    platform: process.platform,
    hasActiveXSupport: Boolean(ActiveXObject)
  };
}

module.exports = {
  convertOdtToHancom,
  getEnvironmentStatus,
  SUPPORTED_FORMATS
};
