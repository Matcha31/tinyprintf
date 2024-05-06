#include <criterion/criterion.h>
#include <criterion/redirect.h>

int tinyprintf(const char *format, ...);

TestSuite(TestTinyPrintf);

Test(TestTinyPrintf, test_smpl, .init = cr_redirect_stdout)
{
    tinyprintf("simple str");
    fflush(stdout);
    cr_assert_stdout_eq_str("simple str");
}

Test(TestTinyPrintf, test_d, .init = cr_redirect_stdout)
{
    tinyprintf("%d", -89);
    fflush(stdout);
    cr_assert_stdout_eq_str("-89");
}

Test(TestTinyPrintf, test_u, .init = cr_redirect_stdout)
{
    tinyprintf("%u", 34);
    fflush(stdout);
    cr_assert_stdout_eq_str("34");
}

Test(TestTinyPrintf, test_o, .init = cr_redirect_stdout)
{
    tinyprintf("%o", 19);
    fflush(stdout);
    cr_assert_stdout_eq_str("23");
}

Test(TestTinyPrintf, test_x, .init = cr_redirect_stdout)
{
    tinyprintf("%x", 42);
    fflush(stdout);
    cr_assert_stdout_eq_str("2a");
}

Test(TestTinyPrintf, test_s, .init = cr_redirect_stdout)
{
    tinyprintf("%s", "my string^^");
    fflush(stdout);
    cr_assert_stdout_eq_str("my string^^");
}

Test(TestTinyPrintf, test_doublep, .init = cr_redirect_stdout)
{
    tinyprintf("%%s", "in your head");
    fflush(stdout);
    cr_assert_stdout_eq_str("%s");
}

Test(TestTinyPrintf, test_sd, .init = cr_redirect_stdout)
{
    tinyprintf("%s [%d] %s", "Hello", 42, "world");
    fflush(stdout);
    cr_assert_stdout_eq_str("Hello [42] world");
}

Test(TestTinyPrintf, test_c, .init = cr_redirect_stdout)
{
    tinyprintf("%c", '&');
    fflush(stdout);
    cr_assert_stdout_eq_str("&");
}

Test(TestTinyPrintf, test_snull, .init = cr_redirect_stdout)
{
    char *s = NULL;
    tinyprintf("%s", s);
    fflush(stdout);
    cr_assert_stdout_eq_str("(null)");
}

Test(TestTinyPrintf, test_percentchar, .init = cr_redirect_stdout)
{
    tinyprintf("%b%k%r%v%w%y%B%D%H%J%K%M%N%O%P%Q%R%T%U%V%W%Y", '&');
    fflush(stdout);
    cr_assert_stdout_eq_str("%b%k%r%v%w%y%B%D%H%J%K%M%N%O%P%Q%R%T%U%V%W%Y");
}

Test(TestTinyPrintf, test_deadcode, .init = cr_redirect_stdout)
{
    tinyprintf("No %x allowed", 3735929054);
    fflush(stdout);
    cr_assert_stdout_eq_str("No deadc0de allowed");
}
