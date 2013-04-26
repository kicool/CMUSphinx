#include <pocketsphinx.h>

#define MODELDIR "/Users/kicoolzhang/Repos/pocketsphinx/model"
#define MODELDIR2 "/Users/kicoolzhang/Repos/pocketsphinx-asr/workdir"

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
			     "-dict", MODELDIR2 "/en.id001.a.dic",
			     "-lm", MODELDIR2 "/en.id001.arpabo",
			     NULL);
	if (config == NULL) return 1;

	ps = ps_init(config);
	if (ps == NULL) return 1;

	fh = fopen("/Users/kicoolzhang/Documents/1.mov", "rb");
	if (fh == NULL) {
		perror("Failed to open goforward.raw");
		return 1;
	}

	rv = ps_decode_raw(ps, fh, NULL, -1);
	if (rv < 0) return 1;
	printf("[K]Decoded No. of samples of audio: %d\n", rv);
	
	hyp = ps_get_hyp(ps, &score, &uttid);
	if (hyp == NULL) return 1;

	printf("Recognized: %s\n", hyp);

	fseek(fh, 0, SEEK_SET);

	rv = ps_start_utt(ps, NULL);
	if (rv < 0) return 1;

	while (!feof(fh)) {
		rv = ps_start_utt(ps, NULL);
		if (rv < 0)
			return 1;
		printf("ready:\n");
		size_t nsamp;
		nsamp = fread(buf, 2, 512, fh);
		printf("read:\n");
		//我们将每次从文件中读取512大小的样本，使用ps_process_raw()把它们放到解码器中:
		rv = ps_process_raw(ps, buf, nsamp, FALSE, FALSE);
		printf("process:\n");
	}

	//我们需要使用ps_end_utt()去标记说话的结尾处：
	rv = ps_end_utt(ps);

	if (rv < 0)
		return 1;

	//以相同精确的方式运行来检索假设的字符串：
	hyp = ps_get_hyp(ps, &score, &uttid);
	if (hyp == NULL)
		return 1;

	printf("Recognized: %s\n", hyp);
	fclose(fh);
	ps_free(ps);
	return 0;
}
