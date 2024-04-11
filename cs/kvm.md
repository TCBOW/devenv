### virsh consoleで接続する

```@guest
  sudo apt install grub2
  sudo vim /etc/default/grub
    GRUB_CMDLINE_LINUX="console=tty0 console=ttyS0,115200n8r"
  sudo grub-mkconfig -o /boot/grub/grub.cfg
  reboot
```

```@host
  sudo virsh console <guest>
```

