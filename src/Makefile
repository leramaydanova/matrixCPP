LIB_NAME	:= s21_matrix_oop.a

CXX			:= g++-14
CXXFLAGS	:= --std=c++20 -pedantic -O2 -Wall -Wextra -Werror

BUILD_DIR	:= build

SRC			:= *.cpp
OBJ		:= *.o
TEST		:= *.[cpph] tests/*

all: $(LIB_NAME) gcov_report

$(LIB_NAME):
	@$(CXX) $(CXXFLAGS) -c $(SRC)
	@ar rcs  $(LIB_NAME) $(OBJ)
	@echo "Created $(LIB_NAME)"

clean:
	@rm -vf *.[oa]  tests/*.[oa] 
	@rm -vf $(LIB_NAME)
	@rm -rvf $(BUILD_DIR)

test: $(BUILD_DIR)
	@cmake --build $(BUILD_DIR)
	@cd build && ctest

$(BUILD_DIR):
	@cmake -S . -B build

gcov_report: test
	@lcov -t "s21_test" -o $(BUILD_DIR)/coverage.info -c -d $(BUILD_DIR) -gcov-tool=/opt/homebrew/bin/gcov-14 --ignore-errors inconsistent
	@lcov --extract $(BUILD_DIR)/coverage.info "*/src/*.cpp" -o $(BUILD_DIR)/coverage_src.info
	@genhtml $(BUILD_DIR)/coverage_src.info -o $(BUILD_DIR)/coverage_report
	@open $(BUILD_DIR)/coverage_report/index.html	


style:
	@clang-format -n $(TEST)


edit:
	@clang-format -i $(TEST)

.PHONY: all clean fclean test style