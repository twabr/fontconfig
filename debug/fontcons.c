#include <fontconfig/fontconfig.h>
#include <stdio.h>
#include <stdlib.h> 

static FcConfig *config = NULL;

// 初始化 Fontconfig 并加载自定义配置
void init_fontconfig(const char *fontsConfPath) 
{     
    printf("into init_fontconfig\n");
    printf("fontsConfPath: %s\n", fontsConfPath);

    if (FcInit()) 
    {
        config = FcConfigCreate();
        if (config) 
        {
            if (FcConfigParseAndLoad(config, (FcChar8 *)fontsConfPath, FcTrue))
            {
                if (!FcConfigBuildFonts (config))
                {
                    FcConfigDestroy (config);
                    return;
                }        
            } 
            else 
            {
                printf("Error parsing and loading config\n");
            }
        } 
        else 
        {
            printf("Error creating config\n");
        }
    } 
    else {
        printf("Error initializing Fontconfig\n");
    }
}

int getFont() 
{   
    printf("into getFont\n");
    if (!config) 
    {
        printf("Error getting FontConfig configuration.\n");
        return 1;
    }

    FcFontSet *sets[2];
    sets[0] = FcConfigGetFonts(config, FcSetSystem);
    sets[1] = FcConfigGetFonts(config, FcSetApplication);

    FcPattern *font;
    FcChar8 *s;

    for (int m = 0; m < 2; m++) 
    {
        FcFontSet *fs = sets[m];
        printf("fs: %p, nfont: %d\n", fs, fs ? fs->nfont : -1);

        for (int i = 0; fs && i < fs->nfont; i++) 
        {
            font = fs->fonts[i];
            s = FcNameUnparse(font);
            if (s) 
            {
                //printf("Font: %s\n", (char *)s);
                free(s);
            }
        }
	fflush(stdout); // 刷新缓冲区

    }
    printf("sets.size: %zu.\n", sizeof(sets) / sizeof(sets[0]));
    
    return 1;
}

int main()
{
    init_fontconfig("/home/wangyao/tools/fonts.conf");
    getFont();

    return 0;
}
