#include <stdio.h>

int main() {
    char response;

    printf("install dwm? (y/n): ");
    scanf(" %c", &response);

    if (response == 'y' || response == 'Y' || response == "yes" || response == "Yes" || response == "YES" || response == "yES" || response == "yeS" || response == "YEs" || response == "YeS" || response == "yEs") {
        printf("installing dwm...\n");
        system("sudo apt-get update; sudo apt-get install -y libxinerama1 libxinerama-dev libx11-dev; sudo pacman -Sy libx11 libxinerama; mkdir $HOME/.config; mkdir $HOME/.config/suckless; wget -P $HOME/.config/suckless https://dl.suckless.org/dwm/dwm-6.4.tar.gz; cd $HOME/.config/suckless; tar -xvf dwm-6.4.tar.gz; cd $HOME/.config/suckless/dwm-6.4; sudo make clean install; cd $OLDPWD; cd $OLDPWD");
        printf("\ndwm installed! located in $HOME/.config/suckless/dwm-6.4\n");
    } else {
        printf("\ninstallation canceled\n");
    }    
    return 0;
}