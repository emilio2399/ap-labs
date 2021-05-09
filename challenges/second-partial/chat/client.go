// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 227.

// Netcat is a simple read/write client for TCP servers.
package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
)

//!+

var username = ""

func main() {
	args := os.Args[1:]
	if len(args) < 4 {
		fmt.Println("Usage: go run client.go -user [username] -server [A.B.C.D:port]")
		os.Exit(3)
	}

	conn, err := net.Dial("tcp", args[3])
	if err != nil {
		log.Fatal(err)
	}
	username = args[1]
	conn.Write([]byte(username))

	done := make(chan struct{})
	go func() {
		_, err := io.Copy(os.Stdout, conn)
		if err != nil {
			log.Fatal(err)
		}
		log.Println("Connection closed")
		done <- struct{}{} // signal the main goroutine
	}()
	mustCopy(conn, os.Stdin)
	conn.Close()
	<-done // wait for background goroutine to finish
}

//!-

func mustCopy(dst io.Writer, src io.Reader) {
	_, err := io.Copy(dst, src)
	if err != nil {
		log.Fatal(err)
	}
}
