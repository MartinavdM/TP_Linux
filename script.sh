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
