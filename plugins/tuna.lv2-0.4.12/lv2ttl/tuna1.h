// generated by lv2ttl2c from
// http://gareus.org/oss/lv2/tuna#one

extern const LV2_Descriptor* lv2_descriptor(uint32_t index);
extern const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index);

static const RtkLv2Description _plugin_tuna_one = {
	&lv2_descriptor,
	&lv2ui_descriptor
	, 0 // uint32_t dsp_descriptor_id
	, 0 // uint32_t gui_descriptor_id
	, "Instrument Tuner" // const char *plugin_human_id
	, (const struct LV2Port[20])
	{
		{ "control", ATOM_IN, nan, nan, nan, "GUI to plugin communication"},
		{ "notify", ATOM_OUT, nan, nan, nan, "Plugin to GUI communication"},
		{ "in", AUDIO_IN, nan, nan, nan, "Audio Input"},
		{ "out", AUDIO_OUT, nan, nan, nan, "Audio output"},
		{ "mode", CONTROL_IN, 0.000000, 0.000000, 8000.000000, "Mode"},
		{ "tuning", CONTROL_IN, 440.000000, 220.000000, 880.000000, "Tuning A440"},
		{ "rms", CONTROL_OUT, nan, -100.000000, -0.000000, "Signal Level (RMS)"},
		{ "freq_out", CONTROL_OUT, nan, 0.000000, 10000.000000, "Detected Frequency"},
		{ "octave", CONTROL_OUT, nan, -1.000000, 10.000000, "Detected Octave"},
		{ "note", CONTROL_OUT, nan, 0.000000, 12.000000, "Detected Note"},
		{ "cent", CONTROL_OUT, nan, -50.000000, 50.000000, "Cent"},
		{ "accuracy", CONTROL_OUT, nan, -100.000000, 100.000000, "Note Stability"},
		{ "strobetoui", CONTROL_OUT, nan, 0.000000, 100.000000, "StrobeToUi"},
		{ "thresholdRMS", CONTROL_IN, -75.000000, -100.000000, 0.000000, "thresholdRMS"},
		{ "thresholdPostFilter", CONTROL_IN, -45.000000, -50.000000, 0.000000, "thresholdPostFilter"},
		{ "thresholdFFT", CONTROL_IN, -40.000000, -50.000000, 10.000000, "thresholdFFT"},
		{ "thresholdOverride", CONTROL_IN, 20.000000, 0.000000, 40.000000, "thresholdOverride"},
		{ "thresholdFundamental", CONTROL_IN, 5.000000, 0.000000, 60.000000, "thresholdFundamental"},
		{ "thresholdOctave", CONTROL_IN, -30.000000, -100.000000, 0.000000, "thresholdOctave"},
		{ "thresholdOvertones", CONTROL_IN, -15.000000, -100.000000, 0.000000, "thresholdvertones"},
	}
	, 20 // uint32_t nports_total
	, 1 // uint32_t nports_audio_in
	, 1 // uint32_t nports_audio_out
	, 0 // uint32_t nports_midi_in
	, 0 // uint32_t nports_midi_out
	, 1 // uint32_t nports_atom_in
	, 1 // uint32_t nports_atom_out
	, 16 // uint32_t nports_ctrl
	, 9 // uint32_t nports_ctrl_in
	, 7 // uint32_t nports_ctrl_out
	, 8192 // uint32_t min_atom_bufsiz
	, false // bool send_time_info
	, UINT32_MAX // uint32_t latency_ctrl_port
};

#ifdef X42_PLUGIN_STRUCT
#undef X42_PLUGIN_STRUCT
#endif
#define X42_PLUGIN_STRUCT _plugin_tuna_one
