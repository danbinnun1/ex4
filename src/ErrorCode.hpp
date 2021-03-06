#pragma once
namespace server_side {
enum ErrorCode {
  NO_ERROR,
  NO_PATH,
  LESS_THAN_TWO_ARGUEMENTS_IN_REQUEST,
  FIRST_REQUEST_WORD_IS_NOT_SOLVE,
  INVALID_PROBLEM_NAME,
  INVALID_ALGORITHM_NAME,
  MORE_THAN_THREE_REQUEST_ARGUEMENTS,
  NO_MATRIX_SENT,
  FIRST_LINE_DOES_NOT_REPRESENT_MATRIX_SIZE,
  MATRIX_HEIGHT_AND_WIDTH_ARE_NOT_INTEGERS,
  HEIGHT_OR_WIDTH_IS_ZERO,
  WRONG_NUMBER_OF_ROWS,
  MATRIX_ROW_LENGTH_NOT_EQUAL_TO_WIDTH,
  MATRIX_VALUE_IS_INVALID,
  START_AND_END_POINTS_DO_NOT_HAVE_TWO_COORDINATES,
  START_AND_END_POINTS_COORDINATED_ARE_NOT_INTEGERS,
  START_OR_END_POINTS_ARE_OUT_OF_THE_MATRIX,
  VALUE_IS_LESS_THAN_ONE,
};
}