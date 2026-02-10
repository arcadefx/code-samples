package tools

import "strconv"

type Tool interface {
	Print(stuff *string)
	Play() string
}

type MyTool struct {
	amount int
}

func NewTool() Tool {
	return &MyTool{
		amount: 42,
	}
}

func (t *MyTool) Print(stuff *string) {
	println(*stuff)
}

func (t *MyTool) Play() string {
	var x int
	for i := 0; i < t.amount; i++ {
		x += i
	}
	return "Playing with tools " + strconv.Itoa(x)
}

func ButterFly() string {
	return "ButterFly"
}
