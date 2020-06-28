// MIT License

#include "user_database.hpp"

#include <restinio/cast_to.hpp>

namespace handler {
namespace user {
restinio::request_handling_status_t add::operator()(const restinio::request_handle_t &req,
                                                    restinio::router::route_params_t params) {
  const auto new_user = user_management::list_modifier(list_).add(nlohmann::json::parse(req->body()));

  return req->create_response()
      .append_header(restinio::http_field::content_type, "application/json")
      .set_body(nlohmann::json(new_user).dump())
      .done();
}

restinio::request_handling_status_t remove::operator()(const restinio::request_handle_t &req,
                                                       restinio::router::route_params_t params) {
  list_.remove(restinio::cast_to<int>(params["index"]));
  return req->create_response(restinio::status_no_content()).done();
}

restinio::request_handling_status_t edit::operator()(const restinio::request_handle_t &req,
                                                     restinio::router::route_params_t params) {
  auto &user = list_.get(restinio::cast_to<int>(params["index"]));
  user_management::user_modifier(user).apply(nlohmann::json::parse(req->body()));

  return req->create_response()
      .append_header(restinio::http_field::content_type, "application/json")
      .set_body(nlohmann::json(user).dump())
      .done();
}

restinio::request_handling_status_t get_user::operator()(const restinio::request_handle_t &req,
                                                         restinio::router::route_params_t params) {
  const auto user = list_.get(restinio::cast_to<int>(params["index"]));
  return req->create_response()
      .append_header(restinio::http_field::content_type, "application/json")
      .set_body(nlohmann::json(user).dump())
      .done();
}

restinio::request_handling_status_t get_list::operator()(const restinio::request_handle_t &req,
                                                         restinio::router::route_params_t params) {
  return req->create_response()
      .append_header(restinio::http_field::content_type, "application/json")
      .set_body(nlohmann::json(list_).dump())
      .done();
}
}  // namespace user
}  // namespace handler