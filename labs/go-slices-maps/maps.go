// Diego Solorzano Ortiz
package main

import (
	"strings"

	"golang.org/x/tour/wc"
)

func WordCount(s string) map[string]int {
	var words = make(map[string]int)
	var list = strings.Fields(s)
	for _, v := range list {
		words[v] = words[v] + 1
	}
	return words
}

func main() {
	wc.Test(WordCount)
}
