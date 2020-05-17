// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 241.

// Crawl2 crawls web links starting with the command-line arguments.
//
// This version uses a buffered channel as a counting semaphore
// to limit the number of concurrent calls to links.Extract.
//
// Crawl3 adds support for depth limiting.
//
package main

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"

	"github.com/todostreaming/gopl.io/ch5/links"
)

// tokens is a counting semaphore used to
// enforce a limit of 20 concurrent requests.
var tokens = make(chan struct{}, 20)

var depth = 1

func crawl(url string, d int) []string {
	fmt.Println(url)
	if d > 0 {
		tokens <- struct{}{} // acquire a token
		list, err := links.Extract(url)
		<-tokens // release the token

		if err != nil {
			log.Print(err)
		}
		return list
	}
	return nil
}

func main() {

	if len(os.Args) < 3 {
		println("Error, correct usage: go run crawl3.go -depth=2 [URL]")
		return
	}

	worklist := make(chan []string)
	var n int // number of pending sends to worklist

	d, err := strconv.Atoi(strings.Split(os.Args[1], "=")[1])

	if err != nil {
		println("Error, correct usage: go run crawl3.go -depth=2 [URL]")
		return
	} else {
		depth = d
	}

	if depth < 1 {
		println("Error, depth must be bigger than 0")
		return
	}

	// Start with the command-line arguments.
	n++
	go func() { worklist <- os.Args[2:] }()

	// Crawl the web concurrently.
	seen := make(map[string]bool)
	for ; n > 0; n-- {
		list := <-worklist
		for _, link := range list {
			if !seen[link] {
				seen[link] = true
				n++
				go func(link string) {
					worklist <- crawl(link, depth)
					if depth > 0 {
						depth--
					}
				}(link)
			}
		}
	}
}
