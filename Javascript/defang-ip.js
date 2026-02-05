
let ip_addr = '10.20.12.255';
ip_addr = ip_addr.replace(/\./g, '[.]');
console.log(ip_addr);

ip_addr = '10.20.12.255';
let out = '';
for(let c of ip_addr) {
    out += c === '.' ? '[.]' : c;
}
console.log(out);
