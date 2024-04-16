
const { spawn } = require('child_process');
const fs = require('fs');
const path = require('path');

const submitBtn = document.getElementById("submitBtn")
submitBtn.addEventListener('click', () => {

    // Get the code from the textarea
    const code = document.getElementById('codeInput').value;
    console.log("code is", code);
    // Only proceed if there is code to compile and run
    if (code.trim() !== '') {
        compileCpp(code);
    } else {
        alert('Please enter some code before submitting.');
    }
});

function compileCpp(code) {
    


    // Save the code to a temporary file
    fs.writeFileSync('includes/temp.cpp', code);

    // Execute compilation process using provided CMakeLists.txt and gcc
    const cmake = spawn('cmake', ['.']);

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
         const parentDir = __dirname;
         const pathResolved = path.resolve(__dirname, "..");
         console.log(pathResolved);
         const make = spawn('make', [], { cwd: pathResolved }); //  we're using Make
         make.stdout.on('data', (data) => {
             console.log(`make stdout: ${data}`);
         });
         make.stderr.on('data', (data) => {
             console.error(`make stderr: ${data}`);
         });
         make.on('close', (code) => {
            //
            let output = '';

            // Execute the compiled program
            const compiledProgram = spawn(path.join(__dirname, '..', 'bin', 'temp'), [], {
                stdio: 'pipe' // Ensure we can capture the output
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

    console.log("end of function compileCpp")
}



/*
// Function to compile C++ code
function compileCpp(code) {
    // Save the code to a temporary file
    fs.writeFileSync('temp.cpp', code);

    // Execute compilation process using provided CMakeLists.txt and gcc
    const cmake = spawn('cmake', ['.']);
    cmake.stdout.on('data', (data) => {
        console.log(`cmake stdout: ${data}`);
    });

    cmake.stderr.on('data', (data) => {
        console.error(`cmake stderr: ${data}`);
    });

    cmake.on('close', (code) => {
        if (code === 0) {
            console.log('CMake configuration successful!');
            const make = spawn('make');
            make.stdout.on('data', (data) => {
                console.log(`make stdout: ${data}`);
            });
            make.stderr.on('data', (data) => {
                console.error(`make stderr: ${data}`);
            });
            make.on('close', (code) => {
                if (code === 0) {
                    console.log('Compilation successful!');
                    // Run the compiled executable if needed
                    const runProcess = spawn('./output');
                    runProcess.stdout.on('data', (data) => {
                        console.log(`Program output: ${data}`);
                    });
                } else {
                    console.error(`Compilation failed with code ${code}`);
                }
            });
        } else {
            console.error(`CMake configuration failed with code ${code}`);
        }
    });
}

// Example usage
const code = `#include <iostream>\nint main() {\nstd::cout << "Hello, world!";\nreturn 0;\n}`;
compileCpp(code);
*/