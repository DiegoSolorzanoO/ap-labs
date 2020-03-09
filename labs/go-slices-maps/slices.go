// Diego Solorzano Ortiz
package main

import "golang.org/x/tour/pic"

func Pic(dx, dy int) [][]uint8 {
	var sli = make([][]uint8, dy)
	for i := 0; i < dy; i++ {
		sli[i] = make([]uint8, dx)
	}
	return sli
}

func main() {
	pic.Show(Pic)
}
