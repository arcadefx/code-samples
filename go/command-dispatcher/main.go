/*
This example demonstrates how to use a map of strings to functions to process messages based on a command string.
The example also demonstrates how to use a map of strings to slices of strings to define permissions for users.

Author: Paul Cardwell
Date: 8/20/2024
Copyright: (c) 2024
*/
package main

import (
	"fmt"
)

type Message struct {
	Msg     string
	Name    string
	Command string
}

// create a map of string to functions
var funcMap = map[string]func(msg Message){
	"ask":          ask,
	"invisibility": invisibility,
	"end":          end,
}

var permissions = map[string][]string{
	"admin": {"ask", "invisibility", "end"},
	"user":  {"ask", "end"},
}

func main() {
	// create a message
	msg := Message{
		Msg:     "How do I avoid the evil wizard?",
		Name:    "Shawn",
		Command: "ask",
	}

	// process the message
	err := processMessage(msg, "user")
	if err != nil {
		fmt.Println(err)
	}

	msg.Command = "invisibility"
	err = processMessage(msg, "admin")
	if err != nil {
		fmt.Println(err)
	}
}

func ask(msg Message) {
	fmt.Println("Hello, ", msg.Name, ". To avoid the evil wizard you must cast the invisibility spell.")
}

func invisibility(msg Message) {
	fmt.Println(msg.Name, ", you are now invisible.")
}

func end(msg Message) {
	fmt.Println("Goodbye, ", msg.Name)
}

func processMessage(message Message, role string) error {
	allowedCommands := permissions[role]
	if !contains(allowedCommands, message.Command) {
		return fmt.Errorf("User does not have permission to execute command: %s", message.Command)
	}

	if f, ok := funcMap[message.Command]; ok {
		f(message)
	}
	return nil
}

func contains(slice []string, item string) bool {
	for _, s := range slice {
		if s == item {
			return true
		}
	}
	return false
}
