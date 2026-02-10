package mini

type MiniPkg interface {
	Print(s string)
}

type Pkg struct {
	name string
}

func NewMiniPkg(
	name string,
) MiniPkg {
	return &Pkg{
		name: name,
	}
}

func (p *Pkg) Print(s string) {
	println(s)
}
