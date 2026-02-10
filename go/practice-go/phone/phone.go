package phone

import "fmt"

const VersionNumber = "1.0.0"

type Phone interface {
	Call(phoneNumber string)
	Info()
}

type PhoneData struct {
	identifier string
}

func NewPhone() Phone {
	return &PhoneData{
		identifier: "MeMobile",
	}
}

func (p *PhoneData) Call(phoneNumber string) {
	fmt.Printf("Dialing %s\n", phoneNumber)
}

func (p *PhoneData) Info() {
	fmt.Printf("ID: %s\n", p.identifier)
}

func Version() {
	fmt.Printf("Version %s\n", VersionNumber)
}
