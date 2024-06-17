#pragma once

struct edge_descr
{
  const size_t start;
  const size_t end;
  const size_t weight;

  edge_descr(const size_t s, const size_t e, const size_t w)
    : start(s), end(e), weight(w)
  {
  }
};
