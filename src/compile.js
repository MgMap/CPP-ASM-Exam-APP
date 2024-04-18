const { spawn } = require('child_process');
const fs = require('fs');
const path = require('path');

function compileCpp(code, fileName) {
    
    // Save the code to a temporary file
    //fs.writeFileSync('main.cpp', code);

    // Execute compilation process using provided CMakeLists.txt and gcc
    const cmake = spawn('cmake', ['-S', '.', '-B', 'build']);

    cmake.stdout.on('data', (data) => {
        console.log(`cmake stdout: ${data}`);
    });

    cmake.stderr.on('data', (data) => {
        console.error(`cmake stderr: ${data}`);
    });

    cmake.on('close', (code) => {

        if (code === 0) {
            console.log('CMake configuration successful! Now trying to run the build');
        

         // Execute build process
         /*
         const parentDir = __dirname;
         const pathResolved = path.resolve(__dirname, "..");
         console.log(pathResolved);
         const make = spawn('make', [], { cwd: pathResolved }); //  we're using Make */

         const parentDir = __dirname;
         const buildDir = path.resolve(parentDir, "../build");

         const make = spawn('cmake', ['--build', buildDir]);
         make.stdout.on('data', (data) => {
             console.log(`make stdout: ${data}`);
         });
         make.stderr.on('data', (data) => {
             console.error(`make stderr: ${data}`);
         });
         make.on('close', (code) => {
            //
            let output = '';

            // execute the compiled program
            const compiledProgram = spawn(path.join(__dirname, '..', 'build', 'bin', fileName), [], {
                stdio: 'pipe' // ensure we can capture the output
            });

            
            compiledProgram.stdout.on('data', (data) => {
                console.log(`Program output: ${data}`);
                output += data.toString();

            });
            compiledProgram.stderr.on('data', (data) => {
                console.error(`Program error: ${data}`);
                
            });
            compiledProgram.on('close', (code) => {
                console.log(`Program exited with code ${code}`);
                // Display the program output in the HTML element
                console.log("program output is", output);
                document.getElementById('codeOutput').innerText = output;
            });
         })

            
            


        } else {
            console.error(`CMake configuration failed with code ${code}`);
        }
    });

}

module.exports = {compileCpp}