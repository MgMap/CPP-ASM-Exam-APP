const { app, BrowserWindow, BrowserView, ipcMain } = require('electron');
const path = require('node:path');

let mainWindow;
let canvasView;

// Handle creating/removing shortcuts on Windows when installing/uninstalling.
if (require('electron-squirrel-startup')) {
  app.quit();
}

function createCanvasView() {
  // Create a BrowserView for the canvas
  canvasView = new BrowserView();

  // Set the web contents of the BrowserView to the Canvas webpage
  canvasView.webContents.loadURL('https://canvas.pasadena.edu');

  // Attach the BrowserView to the main window
  mainWindow.setBrowserView(canvasView);

  // Set the bounds of the BrowserView
  canvasView.setBounds({ x: 32, y: 215, width: 0, height: 0 });


  // Store a reference to the canvas BrowserView in the main window object
  mainWindow.canvasView = canvasView;
}

const createWindow = () => {
  // Create the browser window.
  mainWindow = new BrowserWindow({
    width: 1600,
    height: 1000,
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false,
      preload: path.join(__dirname, 'preload.js'),
    },
  });

  // and load the index.html of the app.
  mainWindow.loadFile(path.join(__dirname, 'index.html'));

  // Create and attach the canvas BrowserView
  createCanvasView();

  // Listen for IPC messages from the renderer process
  ipcMain.on('show-canvas', (event,arg) => {

    canvasView.setBounds({ x: 32, y: 215, width: 1000, height: 770 });
    //x=32, y:215
  });

  ipcMain.on('show-text-editor', () => {
      // Logic to show the Text Editor window
      canvasView.setBounds({ x: 0, y: 0, width: 1, height: 1 });
  });

  // Open the DevTools.
  mainWindow.webContents.openDevTools();

  /*
  // Create a BrowserView
  const browserView = new BrowserView();
  mainWindow.setBrowserView(browserView);
  browserView.setBounds({ x: 500, y: 0, width: 700, height: 800 });

  // Load Canvas URL into the BrowserView
  browserView.webContents.loadURL('https://canvas.pasadena.edu');*/


  // Optional: Open DevTools for debugging
  //browserView.webContents.openDevTools();
};

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.whenReady().then(() => {
  createWindow();

  // On OS X it's common to re-create a window in the app when the
  // dock icon is clicked and there are no other windows open.
  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
      createWindow();
    }

  const win = new BrowserWindow({ width: 800, height: 600 })

  const view = new BrowserView()
  win.setBrowserView(view)
  view.setBounds({ x: 0, y: 0, width: 300, height: 300 })
  view.webContents.loadURL('https://electronjs.org')
  });
});

// Quit when all windows are closed, except on macOS. There, it's common
// for applications and their menu bar to stay active until the user quits
// explicitly with Cmd + Q.
app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and import them here.
