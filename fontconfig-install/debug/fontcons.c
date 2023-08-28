#include <fontconfig/fontconfig.h>
#include <stddef.h>
#include <stdio.h>

static FcConfig *config = NULL;

// 初始化 Fontconfig 并加载自定义配置
void init_fontconfig(const char *fontsConfPath) 
{
    printf("fontsConfPath: %s\n", fontsConfPath);  // 打印传入的路径

    if (FcInit()) 
    {
        printf("Fontconfig initialized\n");
        FcConfigEnableHome(FcTrue); // 启用调试输出
        config = FcConfigCreate();
        if (config) 
        {
            printf("Config created\n");
            if (FcConfigParseAndLoad(config, (FcChar8 *)fontsConfPath, FcTrue)) 
            {
                printf("Config parsed and loaded\n");
                
            } else 
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

// 在自定义配置中查找字体文件路径
const char *find_font_path() 
{
    if (!config) 
        return NULL;

    FcPattern *pattern = FcPatternCreate();
    FcObjectSet *objectSet = FcObjectSetBuild(FC_FILE, NULL);
    FcFontSet *fontSet = FcFontList(config, pattern, objectSet);
    
    if (fontSet && fontSet->nfont > 0) 
    {
        FcChar8 *fontFile;
        if (FcPatternGetString(fontSet->fonts[0], FC_FILE, 0, &fontFile) == FcResultMatch) 
            return (const char *)fontFile;
    }

    return NULL;
}

int main() 
{
    // 调用初始化函数，传递字体配置文件路径
    init_fontconfig("/home/wangyao/tools/fontconfig-install/tt/fonts.conf");

    // 调用查找字体路径函数
    const char *fontPath = find_font_path();
    
    if (fontPath) 
    {
        printf("Font path found: %s\n", fontPath);
    } 
    else 
    {
        printf("Font path not found\n");
    }

    return 0;
}

