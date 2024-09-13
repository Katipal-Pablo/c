#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
} Process;

// Function to implement FCFS scheduling
void fcfs_schedule(Process *processes, int num_processes) {
    int i, total_time = 0;
    printf("FCFS Scheduling:\n");
    for (i = 0; i < num_processes; i++) {
        printf("Process %d: Arrival Time = %d, Burst Time = %d\n",
               processes[i].pid, processes[i].arrival_time, processes[i].burst_time);
        total_time += processes[i].burst_time;
        printf("Total Time: %d\n", total_time);
    }
}

// GUI callback function to handle input and display output
void button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *entry_pid, *entry_arrival_time, *entry_burst_time;
    GtkWidget *label_output;
    Process *processes;
    int num_processes, i;

    // Get the input values from the GUI
    entry_pid = GTK_WIDGET(g_object_get_data(G_OBJECT(widget), "entry_pid"));
    entry_arrival_time = GTK_WIDGET(g_object_get_data(G_OBJECT(widget), "entry_arrival_time"));
    entry_burst_time = GTK_WIDGET(g_object_get_data(G_OBJECT(widget), "entry_burst_time"));

    num_processes = atoi(gtk_entry_get_text(GTK_ENTRY(entry_pid)));
    processes = (Process *)malloc(num_processes * sizeof(Process));

    for (i = 0; i < num_processes; i++) {
        processes[i].pid = i + 1;
        processes[i].arrival_time = atoi(gtk_entry_get_text(GTK_ENTRY(entry_arrival_time)));
        processes[i].burst_time = atoi(gtk_entry_get_text(GTK_ENTRY(entry_burst_time)));
    }

    // Call the FCFS scheduling function
    fcfs_schedule(processes, num_processes);

    // Display the output in the GUI
    label_output = GTK_WIDGET(g_object_get_data(G_OBJECT(widget), "label_output"));
    gtk_label_set_text(GTK_LABEL(label_output), "FCFS Scheduling Complete!");
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *vbox, *hbox, *label, *entry, *button;

    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "FCFS Scheduling");

    // Create a vertical box layout
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create input fields for process details
    hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    label = gtk_label_new("Number of Processes:");
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);

    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
    g_object_set_data(G_OBJECT(window), "entry_pid", entry);

    hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    label = gtk_label_new("Arrival Time:");
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);

    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
    g_object_set_data(G_OBJECT(window), "entry_arrival_time", entry);

    hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    label = gtk_label_new("Burst Time:");
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);

    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
    g_object_set_data(G_OBJECT(window), "entry_burst_time", entry);

    // Create a button to trigger the FCFS scheduling
    button = gtk_button_new_with_label("Schedule");
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), NULL);

    // Create a label to display the output
    label = gtk_label_new("FCFS Scheduling Output:");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
    g_object_set_data(G_OBJECT(window), "label_output", label);

    // Show the window and run the GUI event loop
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
