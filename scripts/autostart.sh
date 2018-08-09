wmname LG3D
#terminusterminusterminusterminus killall compton
killall syndaemon
#killall xfce4-power-manager
feh --bg-fill /home/rchen/wallpaper.jpg &
pkill conky
killall breedaniel 
pkill -f checkEmail
killall nm-applet
killall -r slack 
killall workrave
killall background
killall pulseaudio

# MatrixMonitors
# BothMonitor
if [ -f /home/rchen/.Xresources ]; then 
    LaptopMonitor
else
    BothMonitor
fi

slack &
workrave &
background &
/home/rchen/bin/breedaniel &
/home/rchen/bin/checkEmail.sh &  
/home/rchen/bin/startconky &
#xfce4-power-manager
nm-applet & 
# this is for spotify
start-pulseaudio-x11 &
syndaemon -i 1.0 -d -K 
# compton &
