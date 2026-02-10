package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	const apiCallsTodo = 10
	const maxWorkers = 2

	var wg sync.WaitGroup
	sem := make(chan struct{}, maxWorkers)
	results := make(chan int, apiCallsTodo)

	for i := 0; i < apiCallsTodo; i++ {
		i := i
		wg.Add(1)
		go func() {
			defer wg.Done()
			sem <- struct{}{} // aquire a slot
			fmt.Printf("Making API call %d\n", i)
			worker(i, results)
			fmt.Printf("API call %d done\n", i)
			<-sem // release the slot
		}()
	}
	wg.Wait()
	close(results)

	sum := 0
	for i := 0; i < apiCallsTodo; i++ {
		sum += <-results
	}

	sendResults(sum)
}

func sendResults(sum int) {
	// send results
	fmt.Println("Results sent : ", sum)
}

func worker(i int, results chan int) {
	// do work
	if i%2 == 0 {
		time.Sleep(2 * time.Second)
	} else {
		time.Sleep(1 * time.Second)
	}
	results <- 1
}
