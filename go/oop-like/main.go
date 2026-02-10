package main

import (
	"github.com/go/idea1/grocerybag"
)

func main() {
	bag1 := grocerybag.NewBag(
		[]grocerybag.Item{
			{
				Name: "Apple",
				Cost: 1.5,
			},
		},
	)
	bag1.PrintList()

	bag1.Add("Banana", 0.5)
	bag1.PrintList()

	bag2 := grocerybag.NewBag(
		[]grocerybag.Item{
			{
				Name: "Milk",
				Cost: 2.5,
			},
		},
	)
	bag2.PrintList()

}
