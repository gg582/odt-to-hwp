const { contextBridge, ipcRenderer } = require('electron');
const path = require('path');

contextBridge.exposeInMainWorld('electronAPI', {
  selectOdt: () => ipcRenderer.invoke('dialog:select-odt'),
  selectDestination: (defaultPath) => ipcRenderer.invoke('dialog:select-destination', defaultPath),
  convertDocument: (payload) => ipcRenderer.invoke('converter:convert', payload),
  getEnvironmentStatus: () => ipcRenderer.invoke('converter:status'),
  dirname: (filePath) => path.dirname(filePath),
  joinPath: (...segments) => path.join(...segments)
});
