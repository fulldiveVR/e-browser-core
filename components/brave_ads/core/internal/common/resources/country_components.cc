/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/common/resources/country_components.h"

#include <string_view>

#include "base/containers/fixed_flat_set.h"

namespace {

constexpr auto kCountryComponentIds = base::MakeFixedFlatSet<std::string_view>(
    base::sorted_unique,
    {
        "aafjalakdldginkbeobaiamnfphcdmko", "aaoipmkakdldlippoaocoegnnfnpcokj",
        "adnhangbagjlobdeicimblgcnafegpfb", "aeglmpapdhfhdicbifhnmaoehffffmie",
        "aeiffmlccgeaacefkfknodmnebanekbo", "ahhbponhjohgifhjbjggafboffbimmmg",
        "aiaabcbklimkipbpalfoaehfdebbainb", "ajdiilmgienedlgohldjicpcofnckdmn",
        "alebifccfdpcgpandngmalclpbjpaiak", "alenpijagefjamgompebcjhbfhepnphh",
        "alinepjaedjagibhfjcejemabijbohmi", "anlkmbkbgleadcacchhgdoecllpllknb",
        "aogeahmaehgnkobkmnmkhkimdjpgfgen", "aoidaoefdchfhdjfdffjnnlbfepfkadj",
        "aokfbnlokidoepkhilbmfdkdhajkpbli", "apmipakgigaapfahiojgjgkfgcdekbpp",
        "apndmjdcfbhgfccccdmmeofpdgnlbbif", "bbeoopklmfincipdlffbbphpjefmimmp",
        "bbobjkhpggphapdpcchkbklglkindkcc", "bcnnffpigdndbdohgifflckehcoofigc",
        "bfdagcnfmfaidkkjcmfjmogiefoiglem", "bfhpiebgnciehokapeppcinalnibbnan",
        "bgifagoclclhhoflocdefiklgodpihog", "bhdlolcjjefaidodgffjhpbeeapabpgn",
        "bhkddokohamnindobkmifljnpgijdjdh", "biobhkionbllnfljaapocfpdmhamedkf",
        "blofecpleppfodonanffdbepbiijmklm", "bnonnlpingklaggdalihppicgpaghpop",
        "boeecnnjahpahhockgdcbdlaimpcflig", "bolcbpmofcabjoflcmljongimpbpeagb",
        "bpjdfagamlhoojajkeifbendedaikinl", "cbdjliajiakicmdohhbjbgggacbjdnmn",
        "ccpkbhegiebckfidhnoihgdmddhnmdfh", "cegiaceckhbagmmfcoeebeghiddghbkk",
        "cejbfkalcdepkoekifpidloabepihogd", "celbcocehclbnblfndjfjleagcbbpooc",
        "cfbbahiimladdkhblpkkokkmemlmkbhe", "chbeaiccoofemohdajloflfkblbgdiih",
        "choggjlbfndjppfiidbhmefapnlhcdhe", "chpbioaimigllimaalbibcmjjcfnbpid",
        "ciibjdmjfejjghmnlonlihnjodfckfbo", "cijopjkddpagbkjpnnbjcecfamjbkakp",
        "clcghlkineckendfhkgdpkplofknofjo", "clgbjhhcdihjgbomhpmfdjdiagejadja",
        "cljplhmgochlncaelcabfgeefebhmfnk", "clncjboijmbkcjgkechfhalginbnplpp",
        "cmdlemldhabgmejfognbhdejendfeikd", "cmknopomfihgdpjlnjhjkmogaooeoeic",
        "cobdmgempkofdfhgmbhfckemppmlbjob", "cpbmgmnfoakodmmpppabghhckchppneg",
        "cpjafhooepmhnflmjabfeaiopfbljhpo", "cpjjnbhhjohkkmkkplcfkobjfbjlildd",
        "cpkbkgenaaododkijfnfmgmpekbcfjcg", "cpnhinhihfnhhmoknpbkcifgadjbcjnf",
        "dadpenhnclbbkjfbkgkgecknfjggpbmm", "dckjbnoilglapbgmniiagempimbaicmn",
        "dclpeadnefbjogjcamdglgmmbbgnjcob", "demegfhfekncneocdlflandgegpcoofj",
        "dfmnoondmnbngeilibiicikjenjjeigi", "dggplmjbjalpdgndkigojpikblaiflke",
        "dhcfofldcefkohnjcnfodlbiakgedidd", "dhmcaoadkmoejegjpjgkjhibioemkfni",
        "diacfpapelanfbkmehdpaaohmnkkngge", "djjoaejcadmjbgadeijpbokipgmolnih",
        "djlblammehomffbplemhekjeghekglpc", "dkghhhflbpfknidjbhlophapheggpahk",
        "dkjadbekoidbnlmaomlcjjgkofkechlo", "dlbokjgcdlhkgfeklggoncjhihaebnai",
        "dlfdepidpnibdoblimabdmgpobophapn", "dmdapbmagehdijbdhbdbfjijgmcppjml",
        "dpodaelfodkebmgmmdoecleopjggboln", "ecneelfoifpgnignhipdebhbkgcphmic",
        "efcmpmpbmaehimomnmonodlpnghelnfi", "efpgpbmpbkhadlnpdnjigldeebgacopp",
        "ehkeinmpkojiiacjohbalbnhloiaifig", "ejlnmikcbnjpaaolkheodefhahiabjga",
        "emckddclmcjoilbadmdjdakabpnkdkhk", "enadnicbppimlbpilkeaogmmfpennphn",
        "enkpeojckjlmehbniegocfffdkanjhef", "fahflofbglhemnakgdmillobeencekne",
        "fbmfelhaipnlicodibhjkmeafbcgpfnm", "fbpmbjccnaaeogogeldlomcmlhllgaje",
        "feeklcgpaolphdiamjaolkkcpbeihkbh", "fehpbhdbjpnaibhncpeedfkogiiajcne",
        "fhbmmefncojhnjhbckninoliclloeeac", "fiodhmddlgkgajbhohfdmkliikidmaom",
        "fjefhohmfmokjmnibamjnpiafikmmlef", "fjgjapaemndekhnfeopeoeajfpmlgemo",
        "fjhkoeiglahhpcmgfpalgckcaoaifjkn", "flocoipmnbpcodjfhmkjecjpbkcmkecp",
        "fmobbdfaoifmdjonfklmapdliabjdmjp", "ganmbmiebelpdlnohnabgkkocholelbp",
        "gbbfjnnpelockljikcmjkeodlaebjokm", "gcfgdkmegcjaceeofigbabmjjiojdgnb",
        "gchnahcajhccobheiedkgdpfboljkhge", "gciaobanmdlfkegiikhgdoogegeghhch",
        "gcikmigghagkligpileoekfjmohokjhm", "gfccfpdijajblfnkmddbflphiiibifik",
        "ggclalmmmmgjcoleeficgnnjkpgeinfd", "ghclfflogdfhnjciileceoofmhkneggp",
        "gilieeicpdnkcjbohfhjhpmpjocapbko", "gjkhegliajlngffafldbadcnpfegmkmb",
        "gjknekmnjalchmfjbecifkoohcmlolhp", "gmahgggkpliaoidcaknflpbgpehcjmhc",
        "gmhojjgbbfachddbgojljenplnhialka", "gnamhdlealpfbanappoephfdjeoehggd",
        "gncihmgakhljdlkadibldhdfnocfplci", "gnkmfghehkoegoabhndflbdmfnlgeind",
        "gnmaofjfninpeccldcmlkbinhhohmbck", "haalbaecaigldhgnjfmjbedegjipkdfb",
        "hbiblijpgfgphhfoajjmcgdbhmobbfba", "hefgpgfflbaepfgbafaaadffchekggfg",
        "hehalbiboicjbbcfhckdfeijjjppdhij", "hemccombjdaepjnhhdplhiaedaackooa",
        "hfonhokmgmjionconfpknjfphfahdklo", "hgmkfpcpppjheoknjjfpajfmibkndjdf",
        "hihpbgpfcelklhigbkfnbdgjmpbnabmo", "hkengofpokonjepdafjdeclejledncdj",
        "hkgnnbjmfcelmehmphhbjigedknjobaa", "hknminnkgcjafipipbbalkakppehkpjn",
        "hmmoibmjgckbeejmcfflnngeacaklchb", "hnfmhdkkmcgeppiiohpondjgibepgfeb",
        "hnhakbhiamjojdoajhebemlajheokinm", "iblokdlgekdjophgeonmanpnjihcjkjj",
        "idmipdncpnfbfonogngaimigpbpnenpb", "iefeaaegnnpiadjfoeifapjmflnbjehg",
        "iejekkikpddbbockoldagmfcdbffomfc", "igdomgnppdmcglgohoamnpegjelohlkj",
        "iienfoenehmoepjgljgjdkenjedjfjol", "ikolbkmkinegpoedjeklhfnaidmloifj",
        "iloglofhibeghkfbocphifnfpccmplgd", "imnpbmpnmlmkjpgfnfeplikingjklpej",
        "imoolhehjnpebcjecoinphmohihmbccj", "infpagefbmdijbaigeagmldkjnjdhhfa",
        "inmfjchmafaondfnpgffefgbdmmfgenb", "iobofpagkcicpcijjfmnghgppbghnpdo",
        "jadaiaonajphgnbamppeenldepoajgbf", "jadlfgggcfdhicaoacokfpmccbmedkim",
        "jajkonoepahongnlnfbfmlnpnkjkchof", "jbibpedjodeigdoimlgpikphaabhdbie",
        "jbjodokafbafhemocebljdblgnfajabi", "jcffalbkohmmfjmgkdcphlimplejkmon",
        "jcncoheihebhhiemmbmpfhkceomfipbj", "jdhabeecpolnjdiplbcpjlohmlgdjgjh",
        "jdigggiplmjlocdopbdmjibckpamigij", "jdkdhebphdakbabdbgefjkdbdoagmdec",
        "jejmkjlhckkijknapfhfoogakgoelhen", "jememeholcpjpoahinnlafoiaknnmfgl",
        "jfckclnlfaekpfklphjagmjiphjcchmj", "jicllaljbaldhopinkkegkfpmmnnhmbc",
        "jilipkheolgjanjhhhdmbaleiiblnepe", "jiodmgmkikfbkchgenlamoabbfnobnfh",
        "jlfjphoakpnmhpldmdkdhekopbjmkljn", "jmneklmcodckmpipiekkfaokobhkflep",
        "jnlkpmlmfdipllbnjmjomkddplafclch", "jpapeieehcilkcfpljhopohigdhbnjck",
        "jpejbbflggaiaflclgomjcolpomjmhlh", "kaikhlldfkdjgddjdkangjobahokefeb",
        "kbllnlfaaoonbliendlhmoleflgdekki", "kchkidfjkghdocdicfpmbckmjfgnlndb",
        "kdkakecfnmlfifkhlekmfkmmkpgeckcl", "keggdlgkcfmmopgnogknokiocjjieapm",
        "kennokhomgefcfjjjhckbiidlhmkinca", "kfimhlhdlhimaheficomcahhbaicoele",
        "kfjeoeekjccibpockdjcdjbgagaaopdj", "kgnhcdjacgcanjnbdcmngdeoncckfmfh",
        "kheejcjggceghjdinbcklehfkobloboc", "khgbibnjdanhnoebnfjgpnfbkohdngph",
        "kignebofcmcgmjfiapilgdfkbekmkdmg", "kkfngpdjfcddimfgkgibaccaoehjplkn",
        "kklfafolbojbonkjgifmmkdmaaimminj", "kmdanbbapegbkpjkfdldmekconhnmmmo",
        "kmfkbonhconlbieplamnikedgfbggail", "lanimmipljlbdnajkabaoiklnpcaoakp",
        "lapgbedoccnchodbgfmafpkkhlfmcehe", "lbiagcddmfapjfbebccolcahfppaimmo",
        "lcnaekpkllhpljanlibochejknjflodn", "lfgnglkpngeffaijiomlppnobpchhcgf",
        "lgejdiamednlaeiknhnnjnkofmapfbbf", "lhjcndbhldpnapjddfgohdcdmfibgpon",
        "lhlajkngiihbjjaakfgkencpppeahhfi", "ljfeoddejgcdofgnpgljaeiaemfimgej",
        "ljhceaiogeejahjjblnfaaocgogchpkb", "llmikniomoddmmghodjfbncbidjlhhid",
        "llmmfofcojgcignfnaodhdhdhphhmfmf", "lnbdfmpjjckjhnmahgdojnfnmdmpebfn",
        "lneikknijgnijfnpoahmfkefboallgin", "majdffglhcddbbanjnhfocagmmhobghd",
        "mdojkinfephdfhbfadcnnfcjfniefael", "mdopdmalncfakkimlojioichjbebcaip",
        "megoieebjempmobckocciojgfhfmiejb", "mfnbeofelbcabhloibhpklffiifjcdfl",
        "mhiehehcmljjmpibmpiadoeefnchmbdm", "mhmfclafeemiphfebhnobinkplbmpocm",
        "mjaianjdadeiocokpoanbgjhegficcce", "mjennfbimaafgcoekloojmbhnkophgni",
        "mjhnpmgafkmildljebajibghemlbffni", "mjkmkfbpiegjkbeolgpomaloeiiffodm",
        "mknfcplgmgbfkklaiimdakgjbeonapeh", "mlbgbnccloeobccglpaachnaabgegcni",
        "mmhmpjfgnhibhfccegfohnibkpooppkn", "mmiflfidlgoehkhhkeodfdjpbkkjadgi",
        "mnhglgpnnohpipdeinibpbnlnpledicf", "molpidmcmbmhbicckmbopbmiojddebke",
        "monkjbjmhjepdcaedlejhmjjjcjpiiaa", "nbmopmgpfmalleghhbkablkoamofibpk",
        "ncfbonfnhophngmkkihoieoclepddfhm", "nchncleokkkkdfgbgmenkpkmhnlbibmg",
        "ncldbgolkmlgfkoignkdjehiadnfmlid", "ncmdondkaofghlnhiabnfilafhmabong",
        "ndfnmlonkimafoabeafnaignianecdhf", "nfcegbjbohhjljcdogkmookngaiplbna",
        "nfpgpnagpefhcijfnabpdejiiejplonp", "njlgnoebifbjpafbmnkkchknkinmeljm",
        "nopcbglolocphcdeikfkoeppkhijacij", "npacefioaofgbofilfnhliofkefklipp",
        "oahnhemdhgogkhgljdkhbficecbplmdf", "obihnhimgbeenjgfnlcdbfdgkkgeogdp",
        "obponfmfefkaeehakbehbnnlcbebebhd", "ocegkjjbmlnibhfjmeiaidplhcbdhomd",
        "ochemplgmlglilaflfjnmngpfmpmjgnb", "ocikkcmgfagemkpbbkjlngjomkdobgpp",
        "ocmnmegmbhbfmdnjoppmlbhfcpmedacn", "oejhcomgcgcofdfchkdhkjohnioijofn",
        "oeneodeckioghmhokkmcbijfanjbanop", "ogbkgicanbpgkemjooahemnoihlihonp",
        "ohodaiianeochclnnobadfikohciggno", "ojfkdbfibflfejobeodhoepghgoghkii",
        "okopabpainkagabcmkfnnchaakhimaoe", "onhaidkdpiboaolhnaddeddfaabomchd",
        "paiickhoniddnnlhhdmhjcfemgkgfohn", "panlkcipneniikplpjnoddnhonjljbdp",
        "paoffgbbehbibcihhmboiaebgojdnibj", "pbanoihfljabneihobeplbciopfilajn",
        "pclbpikpdcdondhappcgloeohjgammia", "phihhhnelfclomhodhgalooldjgejgfl",
        "piajfdpbabffhdlmpkaejndbdnohljfn", "pibapallcmncjajdoamgdnmgcbefekgn",
        "pjiglaefpchnekpbkbfngjnfhlcmhgbk", "pkpmecljhbjbiicbnfcfgpgmpehldemm",
        "plpcpclbpkilccbegfbpediidmejaahc", "pmbhpljpfciommdigfblnenpdiapdafl",
        "pmbmbglgbofljclfopjkkompfgedgjhi", "pmlmnjficamnkblapnohndlnhkkoaoco",
        "pnfogoijegjkepejdabehdfadbkpgoed", "pnokpaenadbgpjpmlnoamnmpjbjlfoaf",
        "pofhnfhkonpjephlcjlmbjmlikiaddoc", "pooflbdadogbmjmnnppfmklfjbmoblfa",
        "ppkgobeickbpfmmkbhfgmgiloepdiagn",
    });

}  // namespace

namespace brave_ads {

bool IsValidCountryComponentId(const std::string& id) {
  return kCountryComponentIds.contains(id);
}

}  // namespace brave_ads
