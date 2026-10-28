/*************
* File Name: music_playlist.c
* Aim: Implement a music playlist using circular doubly linked list. it should have the
* functions of play, play next song, play previous song, insert after current, insert at 
* position and delete current song functions as well as a function to create the doubly linked 
* list using user input. songs can be stored as ID numbers. use a tail pointer to keep track of 
* the last song in the playlist. the currently playing song should be tracked using a current 
* pointer. the playlist should wrap around when reaching the end or beginning of the list.
* Author: Sooraj
* Version: 1
* Date: 2026-09-28
***************/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int song_id;
    struct node *next;
    struct node *prev;
};

struct node *tail = NULL;
struct node *current = NULL;

// Function prototypes
void create();
void play();
void play_next();
void play_prev();
void insert_after(int song);
void insert_at_pos(int pos, int song);
void delete_current();

int main() {
    int song, pos;
    create();
    int choice = -1;

    while (choice != 7) {
        printf("\n-------------------------------\n");
        printf("Music Playlist:\nCurrently playing: ");
        if (current == NULL)
            printf("No song\n");
        else
            printf("Song %d\n", current->song_id);

        printf(" 1. Play Song\n");
        printf(" 2. Play Next Song\n");
        printf(" 3. Play Previous Song\n");
        printf(" 4. Insert Song After Current\n");
        printf(" 5. Insert Song at Position\n");
        printf(" 6. Delete Current Song\n");
        printf(" 7. Exit\n");
        printf("Enter Your Choice: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                play();
                break;
            case 2:
                play_next();
                break;
            case 3:
                play_prev();
                break;
            case 4:
                if (tail == NULL) {
                    printf("Playlist is empty. Add songs first.\n");
                    break;
                }
                printf("Enter the song id: ");
                scanf("%d", &song);
                insert_after(song);
                break;
            case 5:
                printf("Enter the song id: ");
                scanf("%d", &song);
                printf("Enter the position (1-based index): ");
                scanf("%d", &pos);
                insert_at_pos(pos, song);
                break;
            case 6:
                delete_current();
                break;
            case 7:
                printf("Exiting playlist application...\n");
                break;
            default:
                printf("Wrong Choice\n");
                break;
        }
    }
    return 0;
}

// Initialize playlist with initial set of songs
void create() {
    int n, song;
    printf("Enter initial number of songs to add: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Starting with empty playlist.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter Song ID %d: ", i + 1);
        scanf("%d", &song);
        
        struct node *new_node = (struct node*)malloc(sizeof(struct node));
        new_node->song_id = song;

        if (tail == NULL) {
            tail = new_node;
            tail->next = tail;
            tail->prev = tail;
        } else {
            new_node->next = tail->next;
            new_node->prev = tail;
            tail->next->prev = new_node;
            tail->next = new_node;
            tail = new_node;
        }
    }
    current = tail->next; // Point current to head (first song)
}

void play() {
    if (current == NULL) {
        printf("Playlist is empty!\n");
    } else {
        printf("Playing Song ID: %d\n", current->song_id);
    }
}

void play_next() {
    if (current == NULL) {
        printf("Playlist is empty!\n");
    } else {
        current = current->next;
        printf("Switched to Next -> Playing Song ID: %d\n", current->song_id);
    }
}

void play_prev() {
    if (current == NULL) {
        printf("Playlist is empty!\n");
    } else {
        current = current->prev;
        printf("Switched to Previous -> Playing Song ID: %d\n", current->song_id);
    }
}

// Insert a new song after the currently playing song
void insert_after(int song) {
    if (current == NULL) {
        printf("Playlist is empty. Cannot insert relative to current.\n");
        return;
    }

    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->song_id = song;

    new_node->next = current->next;
    new_node->prev = current;
    current->next->prev = new_node;
    current->next = new_node;

    if (current == tail) {
        tail = new_node;
    }

    printf("Song %d inserted after Song %d.\n", song, current->song_id);
}

// Insert a song at a 1-based position in the playlist
void insert_at_pos(int pos, int song) {
    if (pos < 1) {
        printf("Invalid position!\n");
        return;
    }

    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->song_id = song;

    // Inserting into an empty list
    if (tail == NULL) {
        if (pos != 1) {
            printf("Position out of bounds. Inserting as first song.\n");
        }
        tail = new_node;
        tail->next = tail;
        tail->prev = tail;
        current = tail;
        printf("Song %d inserted at position 1.\n", song);
        return;
    }

    struct node *head = tail->next;
    
    // Insert at head (Position 1)
    if (pos == 1) {
        new_node->next = head;
        new_node->prev = tail;
        head->prev = new_node;
        tail->next = new_node;
        printf("Song %d inserted at position 1.\n", song);
        return;
    }

    struct node *temp = head;
    int count = 1;

    // Traverse to position - 1
    while (count < pos - 1 && temp != tail) {
        temp = temp->next;
        count++;
    }

    // Insert new node after temp
    new_node->next = temp->next;
    new_node->prev = temp;
    temp->next->prev = new_node;
    temp->next = new_node;

    // Update tail if inserted at the end
    if (temp == tail) {
        tail = new_node;
    }

    printf("Song %d inserted at position %d.\n", song, pos);
}

// Delete the currently active song
void delete_current() {
    if (current == NULL) {
        printf("Playlist is empty! Nothing to delete.\n");
        return;
    }

    struct node *to_delete = current;
    printf("Deleting Song ID: %d...\n", to_delete->song_id);

    // Case 1: Only one node in the playlist
    if (current->next == current) {
        tail = NULL;
        current = NULL;
    } else {
        // Case 2: Multiple nodes
        current->prev->next = current->next;
        current->next->prev = current->prev;

        if (to_delete == tail) {
            tail = current->prev;
        }

        current = current->next; // Move current to next available song
    }

    free(to_delete);
    printf("Song deleted successfully.\n");
}