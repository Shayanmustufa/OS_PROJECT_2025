#include <netinet/in.h>

/*
 *  Port number for chat server.
 *  Also the base for all port numbers allocated to peers.
 */

#define C_SRV_PORT 	12360


#define C_ALIVE 	20

/*
 *  Size of buffer to read and write text messages
 */
#define C_BUFF_SIZE 	1024

/*
 *  Maximum size of display name
 */
#define C_NAME_LEN 	24



/*
 *  message types
 */
#define MSG_ERR     	 0

#define MSG_UP    	 	 1
#define MSG_DOWN      	 2

#define MSG_ALIVE     	11
#define MSG_ACK       	12
#define MSG_NACK       	13

#define MSG_WHO    		21
#define MSG_HDR    		22
#define MSG_PEER    	23

#define MSG_CONN   		31
#define MSG_RESP   		32
#define MSG_TEXT   		33
#define MSG_END   		34

#define MSG_DUMP   		91
#define MSG_SHUTDOWN	92



typedef int msg_type_t;


typedef struct msg_up
{
    msg_type_t	m_type;	 			// = MSG_UP
    in_addr_t   m_addr;				// client's IP address
    char	m_name[C_NAME_LEN + 1];		// client display name
}
    msg_up_t;





typedef struct msg_down
{
    msg_type_t	m_type;	 			// = MSG_UP
    in_addr_t   m_addr;				// client's IP address
    in_port_t   m_port;				// client's assigned port
}
    msg_down_t;



/*
 *  message formats: MSG_ALIVE
 *  Used by clients to maintain their existence.
 */
typedef struct msg_alive
{
    msg_type_t	m_type;	 			// = MSG_ALIVE
    in_addr_t   m_addr;				// client's IP address
    in_port_t   m_port;				// client's assigned port
}
    msg_alive_t;



typedef struct msg_ack
{
    msg_type_t	m_type;				// = MSG_ACK
    in_port_t   m_port;				// client's assigned port
}
    msg_ack_t;



/*
 *  message formats: MSG_NACK
 *  The server responds to MSG_ALIVE from a non-existing client with MSG_NACK.
 *  The client should infer from the response that the server is not aware of
 *  its existence, and should reinitialize, sending a MSG_UP message.
 */
typedef struct msg_nack
{
    msg_type_t	m_type;				// = MSG_NACK
}
    msg_nack_t;




typedef struct msg_who
{
    msg_type_t	m_type;				// = MSG_WHO
}
    msg_who_t;




typedef struct msg_hdr
{
    msg_type_t	m_type;				// = MSG_HDR
    int         m_count;			// number of peers in list
}
    msg_hdr_t;



typedef struct msg_peer
{
    msg_type_t	m_type;				// = MSG_PEER
    in_addr_t   m_addr;				// Peer's IP address
    in_port_t   m_port;				// Peer's port number
    char        m_name[C_NAME_LEN + 1];		// Peer's display name
}
    msg_peer_t;



/*
 *  message formats: MSG_CONN
 *  Used by a peer to request a chat connection:
 */
typedef struct msg_conn
{
    msg_type_t	m_type;				// = MSG_CONN
    in_addr_t   m_addr;				// Sender's IP address
    in_port_t   m_port;				// Sender's port number
	char   	 	m_name[C_NAME_LEN + 1];		// Sender's display name
}
    msg_conn_t;




typedef struct msg_resp
{
    msg_type_t	m_type;				
	int         m_agree;			
}
    msg_resp_t;



/*
 *  message formats: MSG_TEXT
 *  Used by peers to chat:
 */

typedef struct msg_text
{
    msg_type_t	m_type;				
    int			m_size;				
    char        m_text[0];			
}
    msg_text_t;



typedef struct msg_end
{
    msg_type_t	m_type;				
}
    msg_end_t;



typedef struct msg_dump 
{
    msg_type_t	m_type;			
}
    msg_dump_t;




typedef struct msg_shutdown
{
    msg_type_t	m_type;				
}
    msg_shutdown_t;





