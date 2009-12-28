#include "pcapextra.h"

#include <string.h>    // memcpy()
#include <stdlib.h> // malloc(), free()

/* NOTE: All code borrowed from WinPcap */

#ifndef Q_OS_WIN32
pcap_send_queue* pcap_sendqueue_alloc (u_int memsize)
{
    pcap_send_queue *tqueue;

    /* Allocate the queue */
    tqueue = (pcap_send_queue*)malloc(sizeof(pcap_send_queue));
    if(tqueue == NULL){
        return NULL;
    }

    /* Allocate the buffer */
    tqueue->buffer = (char*)malloc(memsize);
    if(tqueue->buffer == NULL){
        free(tqueue);
        return NULL;
    }

    tqueue->maxlen = memsize;
    tqueue->len = 0;

    return tqueue;
}

void pcap_sendqueue_destroy (pcap_send_queue *queue)
{
    free(queue->buffer);
    free(queue);
}

int pcap_sendqueue_queue (pcap_send_queue *queue,
                const struct pcap_pkthdr *pkt_header, const u_char *pkt_data)
{
    if(queue->len + sizeof(struct pcap_pkthdr) + pkt_header->caplen > 
            queue->maxlen)
    {
        return -1;
    }

    /* Copy the pcap_pkthdr header*/
    memcpy(queue->buffer + queue->len, pkt_header, sizeof(struct pcap_pkthdr));
    queue->len += sizeof(struct pcap_pkthdr);

    /* copy the packet */
    memcpy(queue->buffer + queue->len, pkt_data, pkt_header->caplen);
    queue->len += pkt_header->caplen;

    return 0;
}
#endif


