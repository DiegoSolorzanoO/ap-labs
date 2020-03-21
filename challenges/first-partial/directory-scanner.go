package main

import (
	"fmt"
	"os"
	"path/filepath"
	"strconv"
)

// This function displays the final analysis
func displayAnalysis(dir, directories, symlinks, devices, sockets, others string) {
	fmt.Println(`Directory Scanner Tool
+-------------------------+------+
| Path                    | ` + dir + ` |
+-------------------------+------+
| Directories             | ` + directories + `   |
| Symbolic Links          | ` + symlinks + `   |
| Devices                 | ` + devices + `   |
| Sockets                 | ` + sockets + `   |
| Other files             | ` + others + `   |
+-------------------------+------+
		`)
}

// scanDir stands for the directory scanning implementation
func scanDir(dir string) error {
	// Variables are set
	var directories int = 0
	var symlinks int = 0
	var devices int = 0
	var sockets int = 0
	var others int = 0

	// Check if dir is a valid path
	_, notFound := os.Lstat(dir)
	if notFound != nil {
		fmt.Println("Invalid path. Try again with a valid one.")
		return nil
	}

	// Starts the Walk function to analyze each of the files from the dir
	err := filepath.Walk(dir, func(path string, info os.FileInfo, err error) error {
		file, _ := os.Lstat(path)
		if file.IsDir() {
			directories++
		} else if file.Mode()&os.ModeSymlink != 0 {
			symlinks++
		} else if file.Mode()&os.ModeDevice != 0 {
			devices++
		} else if file.Mode()&os.ModeSocket != 0 {
			sockets++
		} else {
			others++
		}
		return nil
	})
	// IF there was an error on the walk function, it returns that
	if err != nil {
		panic(err)
	}
	// After the calculation of values, the variables are displayed
	displayAnalysis(dir, strconv.Itoa(directories), strconv.Itoa(symlinks), strconv.Itoa(devices), strconv.Itoa(sockets), strconv.Itoa(others))
	return nil
}

func main() {

	if len(os.Args) < 2 {
		fmt.Println("Usage: ./dir-scan <directory>")
		os.Exit(1)
	}

	scanDir(os.Args[1])
}
