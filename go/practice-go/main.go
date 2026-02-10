package main

import (
	"fmt"
	"sort"

	"github.com/go/prac1/phone"
	"github.com/go/prac1/tools"
)

func main() {
	nums := []int{10, 40, 30, 20}
	// range
	for i := range nums {
		println(i)
	}

	strings := []string{"a", "b", "c", "d"}
	for _, s := range strings {
		fmt.Printf("%s\n", s)
	}

	tool := tools.NewTool()
	msg := "Hello from tool"
	tool.Print(&msg)

	for i := 0; i < len(msg); i++ {
		fmt.Printf("[%d] = %c\n", i, msg[i])
	}

	fmt.Println(tools.ButterFly())
	fmt.Println(tool.Play())

	chars := []byte{'x', 'b', 'c'}
	for _, x := range chars {
		fmt.Printf("%c\n", x)
	}

	numsSlice := nums[2:]
	fmt.Printf("sliced: %v\n", numsSlice)

	t1 := []int{1, 2, 3, 4}
	t2 := []int{5, 6, 7, 8, 9, 10}
	sort.Slice(t2, func(i, j int) bool {
		return t2[i] < t2[j]
	})
	t3 := append(t2, t1...)
	for _, v := range t3 {
		fmt.Printf("%d ", v)
	}
	fmt.Println()

	// phone
	myPhone := phone.NewPhone()
	myPhone.Info()
	myPhone.Call("555-555-5555")
	myPhone2 := phone.NewPhone()
	myPhone2.Call("777-777-7777")
	phone.Version()

	msg2 := "1234"
	fmt.Println("Reverse:", msg2)

	reversedStr := ""
	for i := len(msg2) - 1; i >= 0; i-- {
		reversedStr += string(msg2[i])
	}
	fmt.Println("Reversed String:", reversedStr)

}
