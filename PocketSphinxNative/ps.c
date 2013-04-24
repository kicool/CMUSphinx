#include <pocketsphinx.h>

#define MODELDIR "/Users/kicoolzhang/Repos/pocketsphinx/model"

int main(int argc, char *argv[])
{
	ps_decoder_t *ps;
	cmd_ln_t *config;
	FILE *fh;
	char const *hyp, *uttid;
	int16 buf[512];
	int rv;        
	int32 score;

	config = cmd_ln_init(NULL, ps_args(), TRUE,
			"-hmm", MODELDIR "/hmm/en_US/hub4wsj_sc_8k",
			"-lm", MODELDIR "/lm/en/turtle.DMP",
			"-dict", MODELDIR "/lm/en/turtle.dic",                             
			NULL);
	return 0;
}
