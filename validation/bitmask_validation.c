#include<stdio.h>
#include<stdlib.h>

typedef unsigned int u32;
typedef unsigned char u8;

struct fq_codel_sched_data{
	u32     *empty_flow_mask;    /* The bitmask array to maintain the empty flows */
	u32     flow_mask_index;     /* The 2 level index to find out the element that has atleast one empty flow. More like a lookup */
};

// $$
/*
 * This function simply gives you the empty flow.
 * It does not flip the bit to mark it as non-empty.
 * A separate function handles the bit flip
 */
static unsigned int get_next_empty_flow(const struct fq_codel_sched_data *q)
{
    u8 right_most_set_zone = 32 - ffs(q->flow_mask_index);
    return right_most_set_zone*32 + (32-ffs(q->empty_flow_mask[right_most_set_zone]));
}

// $$
/*
 * This function does the actual marking of flow as empty.
 */
static void mark_flow_as_empty(struct fq_codel_sched_data *q, int idx)
{
    // Setting a bit will mark the flow as empty
    q->flow_mask_index |= ~(1 << (32 - (idx/32+1)));
    q->empty_flow_mask[idx/32] |= ~(1 << (32 - (idx%32+1)));
}


// $$
/*
 * This function does the actual marking of flow as non-empty.
 */
static void mark_flow_as_non_empty(struct fq_codel_sched_data *q, int idx)
{
    // Clearing a bit will mark the flow as occupied
    q->empty_flow_mask[idx/32] &= ~(1 << (32 - (idx%32+1)));
    if(q->empty_flow_mask[idx/32]==0)
        q->flow_mask_index &= ~(1 << (32 - (idx/32+1)));
}


int main()
{
	struct fq_codel_sched_data *q = (struct fq_codel_sched_data *)(calloc(1,sizeof(struct fq_codel_sched_data)));
	
	// $$
    /* We have 1024 flows. Hence 32*32 = 1024 bits allocated */
    q->empty_flow_mask = (u32 *)calloc(32, sizeof(u32));
    memset(q->empty_flow_mask, 1, 32 * sizeof(u32));

    // $$
    /* Memset the flow_mask_index to 1 */
    memset(&q->flow_mask_index, 1, sizeof(u32));

    printf("\n%d\n",get_next_empty_flow(q));

    q->flow_mask_index = 44;
    q->empty_flow_mask[29] = 46;
    int val = get_next_empty_flow(q);

    printf("\n%d\n",val);

 	mark_flow_as_non_empty(q,val);

 	printf("\n%d\n",q->empty_flow_mask[29]);
 	printf("\n%d\n",q->flow_mask_index);
}