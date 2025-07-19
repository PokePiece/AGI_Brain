#include <stdio.h>
#include <stdlib.h>

#define MAX_CONNECTIONS 10

void call_python_model(const char *prompt, const char *tone, const char *style)
{
    char cmd[1024];
    snprintf(cmd, sizeof(cmd),
             "python Python_Model/main.py '%s' '%s' '%s'", prompt, tone, style);

    // snprintf(cmd, sizeof(cmd),
    //  "Python_Model\\dist\\main.exe '%s' '%s' '%s'", prompt, tone, style);

    FILE *fp = _popen(cmd, "r");
    if (!fp)

    {
        perror("popen failed");
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp))

    {
        printf("%s", buffer);
    }
    _pclose(fp);
}

typedef struct Neuron
{
    int id;
    float value;
    float threshold;
    int fired;
    float weights[MAX_CONNECTIONS];
    struct Neuron *connections[MAX_CONNECTIONS];
    int connection_count;
} Neuron;

typedef struct Brain
{
    Neuron **neurons;
    int neuron_count;
    int capacity;
} Brain;

Neuron *create_neuron(int id)
{
    Neuron *n = malloc(sizeof(Neuron));
    n->id = id;
    n->value = 0.0f;
    n->threshold = 1.0f;
    n->fired = 0;
    n->connection_count = 0;
    for (int i = 0; i < MAX_CONNECTIONS; i++)
    {
        n->connections[i] = NULL;
        n->weights[i] = 1.0f;
    }
    return n;
}

Brain *create_brain(int capacity)
{
    Brain *brain = malloc(sizeof(Brain));
    brain->neurons = malloc(sizeof(Neuron *) * capacity);
    brain->neuron_count = 0;
    brain->capacity = capacity;
    return brain;
}

void add_neuron(Brain *brain, Neuron *neuron)
{
    if (brain->neuron_count < brain->capacity)
    {
        brain->neurons[brain->neuron_count++] = neuron;
    }
    else
    {
        printf("Brain is at full capacity!\n");
    }
}

void connect_neurons(Neuron *from, Neuron *to, float weight)
{
    if (from->connection_count < MAX_CONNECTIONS)
    {
        int idx = from->connection_count;
        from->connections[idx] = to;
        from->weights[idx] = weight;
        from->connection_count++;
        // from->connections[from->connection_count++] = to;
    }
    else
    {
        printf("Neuron %d has max connections!\n", from->id);
    }
}

void propagate_spikes(Neuron *n)
{
    if (!n->fired)
        return;

    for (int i = 0; i < n->connection_count; i++)
    {
        n->connections[i]->value += n->weights[i];
    }

    // Reset after firing
    n->value = 0.0f;
    n->fired = 0;
}

void update_neuron(Neuron *n)
{
    if (n->value >= n->threshold && !n->fired)
    {
        n->fired = 1;
        printf("Neuron %d fired!\n", n->id);
    }
}

void update_firing(Brain *brain)
{
    for (int i = 0; i < brain->neuron_count; i++)
        update_neuron(brain->neurons[i]);
}

void propagate_firing(Brain *brain)
{
    for (int i = 0; i < brain->neuron_count; i++)
        propagate_spikes(brain->neurons[i]);
}

int main()
{
    Brain *brain = create_brain(100);

    Neuron *n1 = create_neuron(1);
    Neuron *n2 = create_neuron(2);

    n1->value += 0.5f;

    connect_neurons(n1, n2, 1.0f);

    add_neuron(brain, n1);
    add_neuron(brain, n2);

    for (int tick = 0; tick < 5; tick++)
    {
        update_firing(brain);

        printf("Tick %d: Neuron 1 value: %.2f, fired: %d\n", tick, n1->value, n1->fired);
        printf("Tick %d: Neuron 2 value: %.2f, fired: %d\n", tick, n2->value, n2->fired);

        propagate_firing(brain);

        n1->value += 0.5f;
    }

    char prompt[512];
    char tone[50] = "happy";
    char style[50] = "conversational";

    while (1)
    {
        printf("Enter prompt (or 'quit' to exit): ");
        if (!fgets(prompt, sizeof(prompt), stdin))
            break;

        // Remove trailing newline
        prompt[strcspn(prompt, "\n")] = 0;

        if (strcmp(prompt, "quit") == 0)
            break;

        call_python_model(prompt, tone, style);

        // You can also call your brain update logic here if desired
    }

    printf("Press Enter to exit...");
    getchar();

    return 0;
}
