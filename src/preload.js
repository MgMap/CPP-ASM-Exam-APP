// See the Electron documentation for details on how to use preload scripts:
// https://www.electronjs.org/docs/latest/tutorial/process-model#preload-scripts
const { contextBridge, ipcRenderer } = require('electron');

contextBridge.exposeInMainWorld('electron', {
    ipcRenderer: {
        send: (channel, data) => ipcRenderer.send(channel, data),
        on: (channel, func) => ipcRenderer.on(channel, (event, ...args) => func(event, ...args)),
        once: (channel, func) => ipcRenderer.once(channel, (event, ...args) => func(event, ...args)),
    },
    compileCpp: (fileName) => ipcRenderer.invoke('compile-cpp', fileName),
    sendEmail: async (submissionInfo) => {
        return ipcRenderer.invoke('send-email', submissionInfo);
    },
});
