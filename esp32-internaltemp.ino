#include <Arduino.h>

#include <MiniShell.h>

#define printf Serial.printf

extern "C" {
    uint8_t temprature_sens_read();
}

static MiniShell shell(&Serial);

static void show_help(const cmd_t *cmds)
{
    for (const cmd_t * cmd = cmds; cmd->cmd != NULL; cmd++) {
        printf("%10s: %s\r\n", cmd->name, cmd->help);
    }
}

static int do_help(int argc, char *argv[]);

static int do_temp(int argc, char *argv[])
{
    uint8_t degf = temprature_sens_read();
    printf("degrees F: %d\n", degf);
    float degc = (degf - 32) / 1.8;
    printf("degrees C: %.1f\n", degc);

    return 0;
}

const cmd_t commands[] = {
    { "help", do_help, "Show help" },
    { "temp", do_temp, "Read builtin temperature sensor" },
    { NULL, NULL, NULL }
};

static int do_help(int argc, char *argv[])
{
    show_help(commands);
    return 0;
}

void setup(void)
{
    Serial.begin(115200);
}

void loop(void)
{
    // process command line
    shell.process(">", commands);
}
