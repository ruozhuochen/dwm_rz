wmname LG3D
killall compton
feh --bg-fill /home/rchen/wallpaper.jpg &
pkill conky
#killall systemGuard
#killall checkEmail.php
killall workrave
killall background
# killall -r slack

workrave &
background &
# slack &
# /home/rchen/bin/systemGuard &
# /home/rchen/bin/checkEmail.php &
/home/rchen/bin/startconky &
compton &
