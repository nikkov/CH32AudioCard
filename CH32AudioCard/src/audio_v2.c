#include "usb_descr.h"

#ifdef CONFIG_USB_HS

#define USBD_VID           0xFFFF
#define USBD_PID           0xFFFE

#if AUDIO_INP_CHANNEL_NUM == 1
#define INPUT_CTRL      DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define INPUT_CH_ENABLE 0x00000000
#elif AUDIO_INP_CHANNEL_NUM == 2
#define INPUT_CTRL      DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define INPUT_CH_ENABLE 0x00000003
#elif AUDIO_INP_CHANNEL_NUM == 3
#define INPUT_CTRL      DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define INPUT_CH_ENABLE 0x00000007
#elif AUDIO_INP_CHANNEL_NUM == 4
#define INPUT_CTRL      DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define INPUT_CH_ENABLE 0x0000000f
#elif AUDIO_INP_CHANNEL_NUM == 5
#define INPUT_CTRL      DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define INPUT_CH_ENABLE 0x0000001f
#elif AUDIO_INP_CHANNEL_NUM == 6
#define INPUT_CTRL      DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define INPUT_CH_ENABLE 0x0000003F
#elif AUDIO_INP_CHANNEL_NUM == 7
#define INPUT_CTRL      DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define INPUT_CH_ENABLE 0x0000007f
#elif AUDIO_INP_CHANNEL_NUM == 8
#define INPUT_CTRL      DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define INPUT_CH_ENABLE 0x000000ff
#endif


#if AUDIO_OUT_CHANNEL_NUM == 1
#define OUTPUT_CTRL     DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define OUTPUT_CH_ENABLE 0x00000000
#elif AUDIO_OUT_CHANNEL_NUM == 2
#define OUTPUT_CTRL     DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define OUTPUT_CH_ENABLE 0x00000003
#elif AUDIO_OUT_CHANNEL_NUM == 3
#define OUTPUT_CTRL     DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define OUTPUT_CH_ENABLE 0x00000007
#elif AUDIO_OUT_CHANNEL_NUM == 4
#define OUTPUT_CTRL     DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define OUTPUT_CH_ENABLE 0x0000000f
#elif AUDIO_OUT_CHANNEL_NUM == 5
#define OUTPUT_CTRL     DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define OUTPUT_CH_ENABLE 0x0000001f
#elif AUDIO_OUT_CHANNEL_NUM == 6
#define OUTPUT_CTRL     DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define OUTPUT_CH_ENABLE 0x0000003F
#elif AUDIO_OUT_CHANNEL_NUM == 7
#define OUTPUT_CTRL     DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define OUTPUT_CH_ENABLE 0x0000007f
#elif AUDIO_OUT_CHANNEL_NUM == 8
#define OUTPUT_CTRL     DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL), DBVAL(BMCONTROL)
#define OUTPUT_CH_ENABLE 0x000000ff
#endif

#define BMCONTROL (AUDIO_V2_FU_CONTROL_MUTE | AUDIO_V2_FU_CONTROL_VOLUME)

#define USB_AUDIO_CONFIG_DESC_SIZ (9 +                                                     \
                                   AUDIO_V2_AC_DESCRIPTOR_INIT_LEN +                       \
                                   AUDIO_V2_SIZEOF_AC_CLOCK_SOURCE_DESC +                  \
                                   AUDIO_V2_SIZEOF_AC_INPUT_TERMINAL_DESC +                \
                                   AUDIO_V2_SIZEOF_AC_FEATURE_UNIT_DESC(AUDIO_OUT_CHANNEL_NUM) + \
                                   AUDIO_V2_SIZEOF_AC_OUTPUT_TERMINAL_DESC +               \
                                   AUDIO_V2_SIZEOF_AC_CLOCK_SOURCE_DESC +                  \
                                   AUDIO_V2_SIZEOF_AC_INPUT_TERMINAL_DESC +                \
                                   AUDIO_V2_SIZEOF_AC_FEATURE_UNIT_DESC(AUDIO_INP_CHANNEL_NUM) +  \
                                   AUDIO_V2_SIZEOF_AC_OUTPUT_TERMINAL_DESC +               \
                                   AUDIO_V2_AS_DESCRIPTOR_INIT_LEN +                       \
                                   AUDIO_V2_AS_DESCRIPTOR_INIT_LEN)

#define AUDIO_AC_SIZ (AUDIO_V2_SIZEOF_AC_HEADER_DESC +                        \
                      AUDIO_V2_SIZEOF_AC_CLOCK_SOURCE_DESC +                  \
                      AUDIO_V2_SIZEOF_AC_INPUT_TERMINAL_DESC +                \
                      AUDIO_V2_SIZEOF_AC_FEATURE_UNIT_DESC(AUDIO_OUT_CHANNEL_NUM) + \
                      AUDIO_V2_SIZEOF_AC_OUTPUT_TERMINAL_DESC +               \
                      AUDIO_V2_SIZEOF_AC_CLOCK_SOURCE_DESC +                  \
                      AUDIO_V2_SIZEOF_AC_INPUT_TERMINAL_DESC +                \
                      AUDIO_V2_SIZEOF_AC_FEATURE_UNIT_DESC(AUDIO_INP_CHANNEL_NUM) +  \
                      AUDIO_V2_SIZEOF_AC_OUTPUT_TERMINAL_DESC)

uint8_t audio_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, USBD_VID, USBD_PID, 0x0001, 0x01),
    USB_CONFIG_DESCRIPTOR_INIT(USB_AUDIO_CONFIG_DESC_SIZ, 0x03, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    AUDIO_V2_AC_DESCRIPTOR_INIT(0x00, 0x03, AUDIO_AC_SIZ, AUDIO_CATEGORY_UNDEF, 0x00, 0x00),
    AUDIO_V2_AC_CLOCK_SOURCE_DESCRIPTOR_INIT(0x01, 0x03, 0x03),
    AUDIO_V2_AC_INPUT_TERMINAL_DESCRIPTOR_INIT(0x02, AUDIO_TERMINAL_STREAMING, 0x01, AUDIO_OUT_CHANNEL_NUM, OUTPUT_CH_ENABLE, 0x0000),
    AUDIO_V2_AC_FEATURE_UNIT_DESCRIPTOR_INIT(0x03, 0x02, OUTPUT_CTRL),
    AUDIO_V2_AC_OUTPUT_TERMINAL_DESCRIPTOR_INIT(0x04, AUDIO_OUTTERM_SPEAKER, 0x03, 0x01, 0x0000),
    AUDIO_V2_AC_CLOCK_SOURCE_DESCRIPTOR_INIT(0x05, 0x03, 0x03),
    AUDIO_V2_AC_INPUT_TERMINAL_DESCRIPTOR_INIT(0x06, AUDIO_INTERM_MIC, 0x05, AUDIO_INP_CHANNEL_NUM, INPUT_CH_ENABLE, 0x0000),
    AUDIO_V2_AC_FEATURE_UNIT_DESCRIPTOR_INIT(0x07, 0x06, INPUT_CTRL),
    AUDIO_V2_AC_OUTPUT_TERMINAL_DESCRIPTOR_INIT(0x08, AUDIO_TERMINAL_STREAMING, 0x07, 0x05, 0x0000),
    AUDIO_V2_AS_DESCRIPTOR_INIT(0x01, 0x02, AUDIO_OUT_CHANNEL_NUM, OUTPUT_CH_ENABLE, AUDIO_OUT_FRAME_SIZE_BYTE, AUDIO_OUT_RESOLUTION_BIT, AUDIO_OUT_EP, AUDIO_OUT_PACKET_SZ, EP_INTERVAL),
    AUDIO_V2_AS_DESCRIPTOR_INIT(0x02, 0x08, AUDIO_INP_CHANNEL_NUM, INPUT_CH_ENABLE, AUDIO_INP_FRAME_SIZE_BYTE, AUDIO_INP_RESOLUTION_BIT, AUDIO_INP_EP,  (AUDIO_INP_PACKET_SZ + AUDIO_INP_FRAME_SIZE_BYTE * AUDIO_INP_CHANNEL_NUM), EP_INTERVAL),
    ///////////////////////////////////////
    /// string0 descriptor
    ///////////////////////////////////////
    USB_LANGID_INIT(USBD_LANGID_STRING),
    ///////////////////////////////////////
    /// string1 descriptor
    ///////////////////////////////////////
    0x14,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'C', 0x00,                  /* wcChar0 */
    'h', 0x00,                  /* wcChar1 */
    'e', 0x00,                  /* wcChar2 */
    'r', 0x00,                  /* wcChar3 */
    'r', 0x00,                  /* wcChar4 */
    'y', 0x00,                  /* wcChar5 */
    'U', 0x00,                  /* wcChar6 */
    'S', 0x00,                  /* wcChar7 */
    'B', 0x00,                  /* wcChar8 */
    ///////////////////////////////////////
    /// string2 descriptor
    ///////////////////////////////////////
    0x28,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'C', 0x00,                  /* wcChar0 */
    'h', 0x00,                  /* wcChar1 */
    'e', 0x00,                  /* wcChar2 */
    'r', 0x00,                  /* wcChar3 */
    'r', 0x00,                  /* wcChar4 */
    'y', 0x00,                  /* wcChar5 */
    'U', 0x00,                  /* wcChar6 */
    'S', 0x00,                  /* wcChar7 */
    'B', 0x00,                  /* wcChar8 */
    ' ', 0x00,                  /* wcChar9 */
    'U', 0x00,                  /* wcChar10 */
    'A', 0x00,                  /* wcChar11 */
    'C', 0x00,                  /* wcChar12 */
    '2', 0x00,                  /* wcChar13 */
    ' ', 0x00,                  /* wcChar14 */
    'D', 0x00,                  /* wcChar15 */
    'E', 0x00,                  /* wcChar16 */
    'M', 0x00,                  /* wcChar17 */
    'O', 0x00,                  /* wcChar18 */
    ///////////////////////////////////////
    /// string3 descriptor
    ///////////////////////////////////////
    0x16,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    '2', 0x00,                  /* wcChar0 */
    '0', 0x00,                  /* wcChar1 */
    '2', 0x00,                  /* wcChar2 */
    '1', 0x00,                  /* wcChar3 */
    '0', 0x00,                  /* wcChar4 */
    '3', 0x00,                  /* wcChar5 */
    '1', 0x00,                  /* wcChar6 */
    '0', 0x00,                  /* wcChar7 */
    '0', 0x00,                  /* wcChar8 */
    '5', 0x00,                  /* wcChar9 */
#ifdef CONFIG_USB_HS
    ///////////////////////////////////////
    /// device qualifier descriptor
    ///////////////////////////////////////
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x01,
    0x00,
#endif
    0x00
};

static const uint8_t speaker_default_sampling_freq_table[] = {
    AUDIO_SAMPLE_FREQ_NUM(1),
    AUDIO_SAMPLE_FREQ_4B(AUDIO_OUT_FREQ_MIN),
    AUDIO_SAMPLE_FREQ_4B(AUDIO_OUT_FREQ_MAX),
    AUDIO_SAMPLE_FREQ_4B(AUDIO_OUT_FREQ_STEP)
};

static const uint8_t mic_default_sampling_freq_table[] = {
    AUDIO_SAMPLE_FREQ_NUM(1),
    AUDIO_SAMPLE_FREQ_4B(AUDIO_INP_FREQ_MIN),
    AUDIO_SAMPLE_FREQ_4B(AUDIO_INP_FREQ_MAX),
    AUDIO_SAMPLE_FREQ_4B(AUDIO_INP_FREQ_STEP)
};

void usbd_audio_get_sampling_freq_table(uint8_t entity_id, uint8_t **sampling_freq_table) {
    if (entity_id == 0x01) {
        printf("spk get freq table\r\n");
        *sampling_freq_table = (uint8_t *)speaker_default_sampling_freq_table;
    } else if (entity_id == 0x05) {
        printf("mic get freq table\r\n");
        *sampling_freq_table = (uint8_t *)mic_default_sampling_freq_table;
    } else {
    }
}

void usbd_audio_set_sampling_freq(uint8_t entity_id, uint8_t ep_ch, uint32_t sampling_freq) {
    uint16_t packet_size = 0;
    if (entity_id == 1) {
        cur_out_freq = sampling_freq;
        packet_size = ((sampling_freq * AUDIO_OUT_FRAME_SIZE_BYTE * AUDIO_OUT_CHANNEL_NUM) / 1000 / (8 / (1 << (EP_INTERVAL - 1))));
        audio_descriptor[18 + USB_AUDIO_CONFIG_DESC_SIZ - AUDIO_V2_AS_DESCRIPTOR_INIT_LEN - 11] = packet_size;
        audio_descriptor[18 + USB_AUDIO_CONFIG_DESC_SIZ - AUDIO_V2_AS_DESCRIPTOR_INIT_LEN - 10] = packet_size >> 8;
        printf("spk set freq %d %ld %d\r\n", entity_id, sampling_freq, packet_size);
    } else if (entity_id == 5) {
        cur_inp_freq = sampling_freq;
        packet_size = ((sampling_freq * AUDIO_INP_FRAME_SIZE_BYTE * AUDIO_INP_CHANNEL_NUM) / 1000 / (8 / (1 << (EP_INTERVAL - 1))));
        audio_descriptor[18 + USB_AUDIO_CONFIG_DESC_SIZ - 11] = packet_size;
        audio_descriptor[18 + USB_AUDIO_CONFIG_DESC_SIZ - 10] = packet_size >> 8;
        printf("mic set freq %d %ld %d\r\n", entity_id, sampling_freq, packet_size);
    }
}

static struct usbd_endpoint audio_in_ep = {
    .ep_cb = usbd_audio_in_callback,
    .ep_addr = AUDIO_INP_EP
};

static struct usbd_endpoint audio_out_ep = {
    .ep_cb = usbd_audio_out_callback,
    .ep_addr = AUDIO_OUT_EP
};

struct usbd_interface intf0;
struct usbd_interface intf1;
struct usbd_interface intf2;

// call from main programm
void audio_init()
{
    usbd_desc_register(audio_descriptor);
    usbd_add_interface(usbd_audio_init_intf(&intf0));
    usbd_add_interface(usbd_audio_init_intf(&intf1));
    usbd_add_interface(usbd_audio_init_intf(&intf2));
    usbd_add_endpoint(&audio_in_ep);
    usbd_add_endpoint(&audio_out_ep);

    usbd_audio_add_entity(0x01, AUDIO_CONTROL_CLOCK_SOURCE);
    usbd_audio_add_entity(0x03, AUDIO_CONTROL_FEATURE_UNIT);
    usbd_audio_add_entity(0x05, AUDIO_CONTROL_CLOCK_SOURCE);
    usbd_audio_add_entity(0x07, AUDIO_CONTROL_FEATURE_UNIT);
}


#endif // CONFIG_USB_HS