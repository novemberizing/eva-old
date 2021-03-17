#include <stdio.h>
#include <stdlib.h>

#include <x/thread.h>
#include <x/dictionary.h>

int main(int argc, char ** argv)
{
    xlogmask_set(xlogtype_assertion);
    xlogconsole_set(xtrue);
    xrandominit();

    
#if 1
    for(xuint32 i = 0; i < 128; i++)
    {
        printf("===============================\n");
        xdictionary * dictionary = xdictionarynew(xnil);
        xuint64 total = xrandomunsigned64(512);
        for(xuint64 i = 0; i < total; i++)
        {
            xval value = xvalunsigned64(xrandomunsigned64(512));
            printf("xdictionaryadd(dictionary, xvalunsigned64(%lu), xnil);\n", value.u64);
            xdictionaryadd(dictionary, value, xnil);
        }

        
        
        xuint64 n = dictionary->size;
        total = xrandomunsigned64(512);
        for(xuint64 i = 0; i < total; i++)
        {
            xval value = xvalunsigned64(xrandomunsigned64(512));
            printf("free(xdictionarydel(dictionary, xvalunsigned64(%lu)));\n", value.u64);
            xdictionarynode * node = xdictionarydel(dictionary, value);
            if(node)
            {
                free(node);
            }
        }
        while(dictionary->size < n / 2)
        {
            xval value = xvalunsigned64(xrandomunsigned64(512));
            printf("free(xdictionarydel(dictionary, xvalunsigned64(%lu)));\n", value.u64);
            xdictionarynode * node = xdictionarydel(dictionary, value);
            if(node)
            {
                free(node);
            }
        }
        xdictionaryrem(dictionary, xnil);
    }
    
#elif 1
xdictionaryadd(dictionary, xvalunsigned64(268), xnil);
xdictionaryadd(dictionary, xvalunsigned64(242), xnil);
xdictionaryadd(dictionary, xvalunsigned64(351), xnil);
xdictionaryadd(dictionary, xvalunsigned64(435), xnil);
xdictionaryadd(dictionary, xvalunsigned64(289), xnil);
xdictionaryadd(dictionary, xvalunsigned64(133), xnil);
xdictionaryadd(dictionary, xvalunsigned64(225), xnil);
xdictionaryadd(dictionary, xvalunsigned64(94), xnil);
xdictionaryadd(dictionary, xvalunsigned64(172), xnil);
xdictionaryadd(dictionary, xvalunsigned64(476), xnil);
xdictionaryadd(dictionary, xvalunsigned64(197), xnil);
xdictionaryadd(dictionary, xvalunsigned64(240), xnil);
xdictionaryadd(dictionary, xvalunsigned64(394), xnil);
xdictionaryadd(dictionary, xvalunsigned64(282), xnil);
xdictionaryadd(dictionary, xvalunsigned64(477), xnil);
xdictionaryadd(dictionary, xvalunsigned64(263), xnil);
xdictionaryadd(dictionary, xvalunsigned64(16), xnil);
xdictionaryadd(dictionary, xvalunsigned64(32), xnil);
xdictionaryadd(dictionary, xvalunsigned64(406), xnil);
xdictionaryadd(dictionary, xvalunsigned64(237), xnil);
xdictionaryadd(dictionary, xvalunsigned64(299), xnil);
xdictionaryadd(dictionary, xvalunsigned64(9), xnil);
xdictionaryadd(dictionary, xvalunsigned64(329), xnil);

free(xdictionarydel(dictionary, xvalunsigned64(219)));
free(xdictionarydel(dictionary, xvalunsigned64(57)));
free(xdictionarydel(dictionary, xvalunsigned64(326)));
free(xdictionarydel(dictionary, xvalunsigned64(226)));
free(xdictionarydel(dictionary, xvalunsigned64(116)));
free(xdictionarydel(dictionary, xvalunsigned64(54)));
free(xdictionarydel(dictionary, xvalunsigned64(250)));
free(xdictionarydel(dictionary, xvalunsigned64(384)));
free(xdictionarydel(dictionary, xvalunsigned64(297)));
free(xdictionarydel(dictionary, xvalunsigned64(89)));
free(xdictionarydel(dictionary, xvalunsigned64(307)));
free(xdictionarydel(dictionary, xvalunsigned64(74)));
free(xdictionarydel(dictionary, xvalunsigned64(222)));
free(xdictionarydel(dictionary, xvalunsigned64(20)));
free(xdictionarydel(dictionary, xvalunsigned64(168)));
free(xdictionarydel(dictionary, xvalunsigned64(394)));
free(xdictionarydel(dictionary, xvalunsigned64(496)));
free(xdictionarydel(dictionary, xvalunsigned64(365)));
free(xdictionarydel(dictionary, xvalunsigned64(123)));
free(xdictionarydel(dictionary, xvalunsigned64(379)));
free(xdictionarydel(dictionary, xvalunsigned64(136)));
free(xdictionarydel(dictionary, xvalunsigned64(88)));
free(xdictionarydel(dictionary, xvalunsigned64(130)));
free(xdictionarydel(dictionary, xvalunsigned64(152)));
free(xdictionarydel(dictionary, xvalunsigned64(121)));
free(xdictionarydel(dictionary, xvalunsigned64(24)));
free(xdictionarydel(dictionary, xvalunsigned64(389)));
free(xdictionarydel(dictionary, xvalunsigned64(420)));
free(xdictionarydel(dictionary, xvalunsigned64(33)));
free(xdictionarydel(dictionary, xvalunsigned64(206)));
free(xdictionarydel(dictionary, xvalunsigned64(241)));
free(xdictionarydel(dictionary, xvalunsigned64(252)));
free(xdictionarydel(dictionary, xvalunsigned64(263)));
#elif 0
xdictionaryadd(dictionary, xvalunsigned64(220), xnil);
xdictionaryadd(dictionary, xvalunsigned64(256), xnil);
xdictionaryadd(dictionary, xvalunsigned64(14), xnil);
xdictionaryadd(dictionary, xvalunsigned64(97), xnil);
xdictionaryadd(dictionary, xvalunsigned64(89), xnil);
xdictionaryadd(dictionary, xvalunsigned64(162), xnil);
xdictionaryadd(dictionary, xvalunsigned64(189), xnil);
xdictionaryadd(dictionary, xvalunsigned64(265), xnil);
xdictionaryadd(dictionary, xvalunsigned64(464), xnil);
xdictionaryadd(dictionary, xvalunsigned64(273), xnil);
xdictionaryadd(dictionary, xvalunsigned64(166), xnil);
xdictionaryadd(dictionary, xvalunsigned64(213), xnil);
xdictionaryadd(dictionary, xvalunsigned64(166), xnil);
xdictionaryadd(dictionary, xvalunsigned64(232), xnil);
xdictionaryadd(dictionary, xvalunsigned64(143), xnil);
xdictionaryadd(dictionary, xvalunsigned64(292), xnil);
xdictionaryadd(dictionary, xvalunsigned64(65), xnil);
xdictionaryadd(dictionary, xvalunsigned64(18), xnil);
xdictionaryadd(dictionary, xvalunsigned64(310), xnil);
xdictionaryadd(dictionary, xvalunsigned64(342), xnil);
xdictionaryadd(dictionary, xvalunsigned64(489), xnil);
xdictionaryadd(dictionary, xvalunsigned64(216), xnil);
xdictionaryadd(dictionary, xvalunsigned64(326), xnil);
xdictionaryadd(dictionary, xvalunsigned64(450), xnil);
xdictionaryadd(dictionary, xvalunsigned64(17), xnil);
xdictionaryadd(dictionary, xvalunsigned64(237), xnil);
xdictionaryadd(dictionary, xvalunsigned64(65), xnil);
xdictionaryadd(dictionary, xvalunsigned64(168), xnil);
xdictionaryadd(dictionary, xvalunsigned64(100), xnil);
xdictionaryadd(dictionary, xvalunsigned64(107), xnil);
xdictionaryadd(dictionary, xvalunsigned64(478), xnil);
xdictionaryadd(dictionary, xvalunsigned64(320), xnil);
xdictionaryadd(dictionary, xvalunsigned64(363), xnil);
xdictionaryadd(dictionary, xvalunsigned64(493), xnil);
xdictionaryadd(dictionary, xvalunsigned64(418), xnil);
xdictionaryadd(dictionary, xvalunsigned64(452), xnil);
xdictionaryadd(dictionary, xvalunsigned64(143), xnil);
xdictionaryadd(dictionary, xvalunsigned64(95), xnil);
xdictionaryadd(dictionary, xvalunsigned64(206), xnil);
xdictionaryadd(dictionary, xvalunsigned64(95), xnil);
xdictionaryadd(dictionary, xvalunsigned64(368), xnil);
xdictionaryadd(dictionary, xvalunsigned64(372), xnil);
xdictionaryadd(dictionary, xvalunsigned64(308), xnil);
xdictionaryadd(dictionary, xvalunsigned64(22), xnil);
xdictionaryadd(dictionary, xvalunsigned64(92), xnil);
xdictionaryadd(dictionary, xvalunsigned64(451), xnil);
xdictionaryadd(dictionary, xvalunsigned64(315), xnil);
xdictionaryadd(dictionary, xvalunsigned64(157), xnil);
xdictionaryadd(dictionary, xvalunsigned64(470), xnil);
xdictionaryadd(dictionary, xvalunsigned64(113), xnil);
xdictionaryadd(dictionary, xvalunsigned64(500), xnil);
xdictionaryadd(dictionary, xvalunsigned64(447), xnil);
xdictionaryadd(dictionary, xvalunsigned64(329), xnil);
xdictionaryadd(dictionary, xvalunsigned64(314), xnil);

free(xdictionarydel(dictionary, xvalunsigned64(346)));
free(xdictionarydel(dictionary, xvalunsigned64(39)));
free(xdictionarydel(dictionary, xvalunsigned64(450)));
free(xdictionarydel(dictionary, xvalunsigned64(2)));
free(xdictionarydel(dictionary, xvalunsigned64(140)));
free(xdictionarydel(dictionary, xvalunsigned64(45)));
free(xdictionarydel(dictionary, xvalunsigned64(480)));
free(xdictionarydel(dictionary, xvalunsigned64(460)));
free(xdictionarydel(dictionary, xvalunsigned64(408)));
free(xdictionarydel(dictionary, xvalunsigned64(461)));
free(xdictionarydel(dictionary, xvalunsigned64(366)));
free(xdictionarydel(dictionary, xvalunsigned64(349)));
free(xdictionarydel(dictionary, xvalunsigned64(93)));
free(xdictionarydel(dictionary, xvalunsigned64(462)));
free(xdictionarydel(dictionary, xvalunsigned64(43)));
free(xdictionarydel(dictionary, xvalunsigned64(188)));
free(xdictionarydel(dictionary, xvalunsigned64(318)));
free(xdictionarydel(dictionary, xvalunsigned64(415)));
free(xdictionarydel(dictionary, xvalunsigned64(497)));
free(xdictionarydel(dictionary, xvalunsigned64(341)));
free(xdictionarydel(dictionary, xvalunsigned64(508)));
free(xdictionarydel(dictionary, xvalunsigned64(436)));
free(xdictionarydel(dictionary, xvalunsigned64(144)));
free(xdictionarydel(dictionary, xvalunsigned64(153)));
free(xdictionarydel(dictionary, xvalunsigned64(394)));
free(xdictionarydel(dictionary, xvalunsigned64(257)));
free(xdictionarydel(dictionary, xvalunsigned64(141)));
free(xdictionarydel(dictionary, xvalunsigned64(329)));
free(xdictionarydel(dictionary, xvalunsigned64(74)));
free(xdictionarydel(dictionary, xvalunsigned64(456)));
free(xdictionarydel(dictionary, xvalunsigned64(202)));
free(xdictionarydel(dictionary, xvalunsigned64(420)));
free(xdictionarydel(dictionary, xvalunsigned64(495)));
free(xdictionarydel(dictionary, xvalunsigned64(140)));
free(xdictionarydel(dictionary, xvalunsigned64(422)));
free(xdictionarydel(dictionary, xvalunsigned64(123)));
free(xdictionarydel(dictionary, xvalunsigned64(185)));
free(xdictionarydel(dictionary, xvalunsigned64(390)));
free(xdictionarydel(dictionary, xvalunsigned64(72)));
free(xdictionarydel(dictionary, xvalunsigned64(82)));
free(xdictionarydel(dictionary, xvalunsigned64(340)));
free(xdictionarydel(dictionary, xvalunsigned64(438)));
free(xdictionarydel(dictionary, xvalunsigned64(431)));
free(xdictionarydel(dictionary, xvalunsigned64(433)));
free(xdictionarydel(dictionary, xvalunsigned64(388)));
free(xdictionarydel(dictionary, xvalunsigned64(474)));
free(xdictionarydel(dictionary, xvalunsigned64(109)));
free(xdictionarydel(dictionary, xvalunsigned64(195)));
free(xdictionarydel(dictionary, xvalunsigned64(377)));
free(xdictionarydel(dictionary, xvalunsigned64(94)));
free(xdictionarydel(dictionary, xvalunsigned64(24)));
free(xdictionarydel(dictionary, xvalunsigned64(373)));
free(xdictionarydel(dictionary, xvalunsigned64(19)));
free(xdictionarydel(dictionary, xvalunsigned64(168)));
free(xdictionarydel(dictionary, xvalunsigned64(15)));
free(xdictionarydel(dictionary, xvalunsigned64(413)));
free(xdictionarydel(dictionary, xvalunsigned64(425)));
free(xdictionarydel(dictionary, xvalunsigned64(156)));
free(xdictionarydel(dictionary, xvalunsigned64(231)));
free(xdictionarydel(dictionary, xvalunsigned64(499)));
free(xdictionarydel(dictionary, xvalunsigned64(100)));
#else
    xdictionaryadd(dictionary, xvalunsigned64(149), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(32), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(129), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(45), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(167), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(88), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(1), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(64), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(103), xnil);

    xdictionaryadd(dictionary, xvalunsigned64(169), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(275), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(189), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(221), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(220), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(465), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(340), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(329), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(270), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(411), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(59), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(11), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(154), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(241), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(401), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(63), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(304), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(45), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(392), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(480), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(67), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(452), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(105), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(146), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(166), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(214), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(15), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(184), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(495), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(76), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(472), xnil);
    xdictionaryadd(dictionary, xvalunsigned64(153), xnil);

    // free(xdictionarydel(dictionary, xvalunsigned64(150)));
    // free(xdictionarydel(dictionary, xvalunsigned64(374)));
    // free(xdictionarydel(dictionary, xvalunsigned64(60)));
    // free(xdictionarydel(dictionary, xvalunsigned64(103)));
    // free(xdictionarydel(dictionary, xvalunsigned64(202)));
    // free(xdictionarydel(dictionary, xvalunsigned64(389)));
    // free(xdictionarydel(dictionary, xvalunsigned64(373)));
    // free(xdictionarydel(dictionary, xvalunsigned64(101)));
    // free(xdictionarydel(dictionary, xvalunsigned64(448)));
    // free(xdictionarydel(dictionary, xvalunsigned64(384)));
    // free(xdictionarydel(dictionary, xvalunsigned64(255)));
    // free(xdictionarydel(dictionary, xvalunsigned64(177)));
    // free(xdictionarydel(dictionary, xvalunsigned64(274)));
    // free(xdictionarydel(dictionary, xvalunsigned64(319)));
    // free(xdictionarydel(dictionary, xvalunsigned64(482)));
    // free(xdictionarydel(dictionary, xvalunsigned64(319)));
    // free(xdictionarydel(dictionary, xvalunsigned64(199)));
    // free(xdictionarydel(dictionary, xvalunsigned64(450)));
    // free(xdictionarydel(dictionary, xvalunsigned64(386)));
    // free(xdictionarydel(dictionary, xvalunsigned64(139)));
    // free(xdictionarydel(dictionary, xvalunsigned64(44)));
    // free(xdictionarydel(dictionary, xvalunsigned64(20)));
    // free(xdictionarydel(dictionary, xvalunsigned64(306)));
    // free(xdictionarydel(dictionary, xvalunsigned64(258)));
    // free(xdictionarydel(dictionary, xvalunsigned64(36)));
    // free(xdictionarydel(dictionary, xvalunsigned64(490)));
    // free(xdictionarydel(dictionary, xvalunsigned64(242)));
    // free(xdictionarydel(dictionary, xvalunsigned64(112)));
    // free(xdictionarydel(dictionary, xvalunsigned64(450)));
    // free(xdictionarydel(dictionary, xvalunsigned64(395)));
    // free(xdictionarydel(dictionary, xvalunsigned64(464)));
    // free(xdictionarydel(dictionary, xvalunsigned64(88)));
    // free(xdictionarydel(dictionary, xvalunsigned64(257)));
    // free(xdictionarydel(dictionary, xvalunsigned64(12)));
    // free(xdictionarydel(dictionary, xvalunsigned64(192)));
    // free(xdictionarydel(dictionary, xvalunsigned64(459)));
    free(xdictionarydel(dictionary, xvalunsigned64(401)));
#endif // 0

    

    xlogterm();
    return 0;
}