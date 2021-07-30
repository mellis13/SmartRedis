#include "../../../third-party/catch/catch.hpp"
#include "command.h"

using namespace SmartRedis;

using Types = std::tuple<int, long, long long, unsigned, unsigned long,
                         unsigned long long, float, double, long double>;

TEMPLATE_LIST_TEST_CASE("Test templated add_fields method for Command",
                        "[Command][list]", Types)
{
    Command cmd;
    TestType field = (TestType) 4;
    const std::vector<TestType> fields = {field};

    cmd.add_fields(fields, true);

    CHECK(*cmd.begin() == std::to_string(field));
}

SCENARIO("Testing Command object", "[Command]")
{

    GIVEN("An empty Command object")
    {
        Command cmd;

        WHEN("The first field is attempted to be retrieved")
        {

            THEN("A runtime error is thrown")
            {
                CHECK_THROWS_AS(cmd.first_field(), std::runtime_error);
            }
        }
    }

    GIVEN("A Command object with a single field")
    {
        Command cmd;
        std::string field = "MINIBATCHSIZE";
        cmd.add_field(field, true);

        WHEN("Iterators from the Command object's "
             "_fields data member are retrieved")
        {
            Command::iterator begin_it = cmd.begin();
            Command::iterator end_it = cmd.end();
            Command::const_iterator cbegin_it = cmd.cbegin();
            Command::const_iterator cend_it = cmd.cend();

            THEN("The iterators that were retrieved are the correct iterators")
            {
                CHECK(*cmd.begin() == field);
                CHECK(*cmd.cbegin() == field);
                begin_it++;
                cbegin_it++;
                CHECK(begin_it == end_it);
                CHECK(cbegin_it == cend_it);
            }
        }
    }

    AND_GIVEN("A Command object")
    {
        Command cmd;

        WHEN("Fields are added to the Command object in every possible manner")
        {
            // create the fields
            std::string field_1 = "TAG";
            char field_2[4] = "DEL";
            const char field_3[7] = "RENAME";
            char field_4[7] = "SOURCE";
            size_t field_size_4 = std::strlen(field_4);
            std::string field_5 = "INPUTS";
            std::vector<std::string> fields_1 = {"EXISTS", "META", "BLOB"};

            // define necessary variables for testing
            std::string output = " TAG DEL RENAME SOURCE INPUTS EXISTS META BLOB";
            std::vector<std::string> sorted_keys =
                {"BLOB", "DEL", "EXISTS", "META", "RENAME"};
            std::vector<std::string> cmd_keys;

            // add the fields to the Command
            cmd.add_field(field_1, false);
            cmd.add_field(field_2, true);
            cmd.add_field(field_3, true);
            cmd.add_field_ptr(field_4, field_size_4);
            cmd.add_field_ptr(field_5);
            cmd.add_fields(fields_1, true);

            THEN("The Command object is structured correctly")
            {
                CHECK(cmd.has_keys() == true);
                CHECK(cmd.first_field() == field_1);
                CHECK(output == cmd.to_string());

                cmd_keys = cmd.get_keys();
                std::sort(cmd_keys.begin(), cmd_keys.end());
                CHECK(cmd_keys == sorted_keys);
            }

            AND_THEN("A new Command object can be constructed "
                     "with the copy constructor")
            {
                Command* cmd_cpy = new Command(cmd);

                Command::const_iterator it = cmd.cbegin();
                Command::const_iterator it_end = cmd.cend();
                Command::const_iterator it_cpy = cmd_cpy->cbegin();
                Command::const_iterator it_end_cpy = cmd_cpy->cend();

                while (it != it_end) {
                    REQUIRE(it_cpy != it_end_cpy);
                    CHECK(*it == *it_cpy);
                    it++;
                    it_cpy++;
                }
                CHECK(it_cpy == it_end_cpy);

                cmd_keys = cmd.get_keys();
                std::vector<std::string> cmd_keys_cpy = cmd_cpy->get_keys();
                std::sort(cmd_keys.begin(), cmd_keys.end());
                std::sort(cmd_keys_cpy.begin(), cmd_keys_cpy.end());
                CHECK(cmd_keys_cpy == cmd_keys);

                delete cmd_cpy;

                // Ensure the state of the original Command object is preserved
                CHECK(cmd.has_keys() == true);
                CHECK(cmd.first_field() == field_1);
                CHECK(output == cmd.to_string());

                cmd_keys = cmd.get_keys();
                std::sort(cmd_keys.begin(), cmd_keys.end());
                CHECK(cmd_keys == sorted_keys);

            }

            AND_THEN("The Command object can be copied "
                     "with the assignment operator")
            {
                Command* cmd_cpy = new Command;
                cmd_cpy->add_field("field_to_be_destroyed", true);

                *cmd_cpy = cmd;

                Command::const_iterator it = cmd.cbegin();
                Command::const_iterator it_end = cmd.cend();
                Command::const_iterator it_cpy = cmd_cpy->cbegin();
                Command::const_iterator it_end_cpy = cmd_cpy->cend();

                while (it != it_end) {
                    REQUIRE(it_cpy != it_end_cpy);
                    CHECK(*it == *it_cpy);
                    it++;
                    it_cpy++;
                }
                CHECK(it_cpy == it_end_cpy);

                cmd_keys = cmd.get_keys();
                std::vector<std::string> cmd_keys_cpy = cmd_cpy->get_keys();
                std::sort(cmd_keys.begin(), cmd_keys.end());
                std::sort(cmd_keys_cpy.begin(), cmd_keys_cpy.end());
                CHECK(cmd_keys_cpy == cmd_keys);

                delete cmd_cpy;

                // Ensure the state of the original Command object is preserved
                CHECK(cmd.has_keys() == true);
                CHECK(cmd.first_field() == field_1);
                CHECK(output == cmd.to_string());

                cmd_keys = cmd.get_keys();
                std::sort(cmd_keys.begin(), cmd_keys.end());
                CHECK(cmd_keys == sorted_keys);
            }
        }
    }

    AND_GIVEN("A Command object on the heap")
    {
        Command* cmd = new Command;

        // define fields
        std::string field_1 = "TAG";
        char field_2[4] = "DEL";
        const char field_3[7] = "RENAME";
        char field_4[7] = "SOURCE";
        size_t field_size_4 = std::strlen(field_4);
        std::string field_5 = "INPUTS";
        std::vector<std::string> fields_1 = {"EXISTS", "META", "BLOB"};
        std::string_view field_sv = std::string_view(field_4, field_size_4);

        // define necessary variables for testing
        std::string output = " TAG DEL RENAME SOURCE INPUTS "
                             "EXISTS META BLOB SOURCE";
        std::vector<std::string> sorted_keys =
            {"BLOB", "DEL", "EXISTS", "META", "RENAME"};
        std::vector<std::string> cmd_keys;

        // add fields
        cmd->add_field(field_1, false);
        cmd->add_field(field_2, true);
        cmd->add_field(field_3, true);
        cmd->add_field_ptr(field_4, field_size_4);
        cmd->add_field_ptr(field_5);
        cmd->add_fields(fields_1, true);
        cmd->add_field_ptr(field_sv);

        THEN("The Command object can be copied with the assign operator "
             "and then can be deleted while preserving the original "
             "Command's state")
        {
            Command* cmd_cpy = new Command;
            cmd_cpy->add_field("field_to_be_destroyed", true);

            *cmd_cpy = *cmd;

            Command::const_iterator it = cmd->cbegin();
            Command::const_iterator it_end = cmd->cend();
            Command::const_iterator it_cpy = cmd_cpy->cbegin();
            Command::const_iterator it_end_cpy = cmd_cpy->cend();

            while (it != it_end) {
                REQUIRE(it_cpy != it_end_cpy);
                CHECK(*it == *it_cpy);
                it++;
                it_cpy++;
            }
            CHECK(it_cpy == it_end_cpy);

            cmd_keys = cmd->get_keys();
            std::vector<std::string> cmd_keys_cpy = cmd_cpy->get_keys();
            std::sort(cmd_keys.begin(), cmd_keys.end());
            std::sort(cmd_keys_cpy.begin(), cmd_keys_cpy.end());
            CHECK(cmd_keys_cpy == cmd_keys);

            delete cmd;

            // Ensure the state of the original Command object is preserved
            CHECK(cmd_cpy->has_keys() == true);
            CHECK(cmd_cpy->first_field() == field_1);
            CHECK(output == cmd_cpy->to_string());

            cmd_keys = cmd_cpy->get_keys();
            std::sort(cmd_keys.begin(), cmd_keys.end());
            CHECK(cmd_keys == sorted_keys);
            delete cmd_cpy;
        }

        AND_THEN("The Command object can be copied with the copy "
                 "constructor and then can be deleted while "
                 "preserving the original Command's state")
        {
            Command* cmd_cpy = new Command(*cmd);

            Command::const_iterator it = cmd->cbegin();
            Command::const_iterator it_end = cmd->cend();
            Command::const_iterator it_cpy = cmd_cpy->cbegin();
            Command::const_iterator it_end_cpy = cmd_cpy->cend();

            while (it != it_end) {
                REQUIRE(it_cpy != it_end_cpy);
                CHECK(*it == *it_cpy);
                it++;
                it_cpy++;
            }
            CHECK(it_cpy == it_end_cpy);

            cmd_keys = cmd->get_keys();
            std::vector<std::string> cmd_keys_cpy = cmd_cpy->get_keys();
            std::sort(cmd_keys.begin(), cmd_keys.end());
            std::sort(cmd_keys_cpy.begin(), cmd_keys_cpy.end());
            CHECK(cmd_keys_cpy == cmd_keys);

            delete cmd;

            // Ensure the state of the original Command object is preserved
            CHECK(cmd_cpy->has_keys() == true);
            CHECK(cmd_cpy->first_field() == field_1);
            CHECK(output == cmd_cpy->to_string());

            cmd_keys = cmd_cpy->get_keys();
            std::sort(cmd_keys.begin(), cmd_keys.end());
            CHECK(cmd_keys == sorted_keys);
            delete cmd_cpy;
        }
    }
}