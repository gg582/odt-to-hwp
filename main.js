const path = require('path');
const { app, BrowserWindow, ipcMain, dialog } = require('electron');
const { convertOdtToHancom, getEnvironmentStatus, SUPPORTED_FORMATS } = require('./src/converter/hwpConverter');

const isDevelopment = process.env.NODE_ENV === 'development';

function createWindow() {
  const mainWindow = new BrowserWindow({
    width: 960,
    height: 640,
    webPreferences: {
      preload: path.join(__dirname, 'preload.js'),
      contextIsolation: true,
      nodeIntegration: false
    }
  });

  mainWindow.setMenu(null);
  mainWindow.loadFile(path.join(__dirname, 'src/renderer/index.html'));

  if (isDevelopment) {
    mainWindow.webContents.openDevTools();
  }
}

app.whenReady().then(() => {
  ipcMain.handle('dialog:select-odt', async () => {
    const { canceled, filePaths } = await dialog.showOpenDialog({
      properties: ['openFile'],
      filters: [{ name: 'OpenDocument Text', extensions: ['odt'] }]
    });
    if (canceled || !filePaths.length) {
      return null;
    }
    return filePaths[0];
  });

  ipcMain.handle('dialog:select-destination', async (event, defaultName) => {
    const { canceled, filePath } = await dialog.showSaveDialog({
      defaultPath: defaultName,
      filters: [
        {
          name: 'Hancom Documents',
          extensions: Object.values(SUPPORTED_FORMATS).map((format) => format.extension.replace('.', ''))
        }
      ]
    });

    if (canceled || !filePath) {
      return null;
    }

    return filePath;
  });

  ipcMain.handle('converter:status', async () => getEnvironmentStatus());

  ipcMain.handle('converter:convert', async (event, payload) => {
    try {
      const outputPath = convertOdtToHancom(payload.sourcePath, {
        outputDir: payload.outputDir,
        format: payload.format
      });

      return { success: true, outputPath };
    } catch (error) {
      return { success: false, message: error.message };
    }
  });

  createWindow();

  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
      createWindow();
    }
  });
});

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});
