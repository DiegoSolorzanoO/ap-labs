package main

import (
	"fmt"
	"log"
	"net"
	"os"
	"strings"
)

func main() {
	port1 := strings.Split(os.Args[1], ":")[1]
	port2 := strings.Split(os.Args[2], ":")[1]
	port3 := strings.Split(os.Args[3], ":")[1]

	conn1, err1 := net.Dial("tcp", "localhost:"+port1)
	conn2, err2 := net.Dial("tcp", "localhost:"+port2)
	conn3, err3 := net.Dial("tcp", "localhost:"+port3)

	if err1 != nil {
		log.Fatalln(err1)
	}
	if err2 != nil {
		log.Fatalln(err2)
	}
	if err3 != nil {
		log.Fatalln(err3)
	}

	for {
		data1 := make([]byte, 512)
		n1, err1 := conn1.Read(data1)
		if err1 != nil {
			panic(err1)
		}
		s1 := string(data1[:n1])

		data2 := make([]byte, 512)
		n2, err2 := conn2.Read(data2)
		if err2 != nil {
			panic(err2)
		}
		s2 := string(data2[:n2])

		data3 := make([]byte, 512)
		n3, err3 := conn3.Read(data3)
		if err3 != nil {
			panic(err3)
		}
		s3 := string(data3[:n3])

		fmt.Print("US/Eastern    : " + s1)
		fmt.Print("Asia/Tokyo    : " + s2)
		fmt.Print("Europe/London : " + s3)
	}
}
