#include <stdio.h>
#include <string.h>

struct mac_entry
{
    char mac[20];
    int port;
};

struct mac_entry table[10];
int count = 0;

void learn_mac(char mac[], int port)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (strcmp(table[i].mac, mac) == 0)
        {
            table[i].port = port;
            return;
        }
    }

    if (count < 10)
    {
        strcpy(table[count].mac, mac);
        table[count].port = port;
        count++;
    }
    else
    {
        printf("MAC table is full! Cannot learn a new MAC address.\\n");
    }
}

int find_mac(char mac[])
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (strcmp(table[i].mac, mac) == 0)
            return table[i].port;
    }

    return -1;
}

int main(void)
{
    char src[20], dest[20];
    int incoming, outgoing;

    printf("Enter Source MAC: ");
    scanf("%19s", src);

    printf("Enter Destination MAC: ");
    scanf("%19s", dest);

    printf("Enter Incoming Port: ");
    scanf("%d", &incoming);

    learn_mac(src, incoming);
    outgoing = find_mac(dest);

    if (outgoing == -1)
    {
        printf("Destination unknown!\\n");
        printf("Flooding frame to other ports.\\n");
    }
    else if (outgoing == incoming)
    {
        printf("Destination is on same port.\\n");
        printf("Frame discarded.\\n");
    }
    else
    {
        printf("Destination found!\\n");
        printf("Forwarding frame to Port %d\\n", outgoing);
    }

    return 0;
}
