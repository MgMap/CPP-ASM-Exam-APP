require.config({ paths: { vs: "../node_modules/monaco-editor/min/vs" } });
      window.MonacoEnvironment = {
        getWorkerUrl: function (workerId, label) {
          return `data:text/javascript;charset=utf-8,${encodeURIComponent(`
            self.MonacoEnvironment = {
              baseUrl: '../node_modules/monaco-editor/min/'
            };
            importScripts('../node_modules/monaco-editor/min/vs/base/worker/workerMain.js');`)}`;
        },
      };
