package grocerybag

import "fmt"

type Bag interface {
	Add(name string, cost float64)
	PrintList()
}

type Item struct {
	Name string
	Cost float64
}

type GroceryBag struct {
	Items []Item
}

func NewBag(
	items []Item,
) Bag {
	return &GroceryBag{
		Items: items,
	}
}

func (t *GroceryBag) Add(name string, cost float64) {
	t.Items = append(t.Items, Item{
		Name: name,
		Cost: cost,
	})
}

func (t *GroceryBag) PrintList() {
	fmt.Println("Items in the bag: ")
	for _, item := range t.Items {
		fmt.Println(item.Name, " - ", item.Cost)
	}
	fmt.Println()
}
